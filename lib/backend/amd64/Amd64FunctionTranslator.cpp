#include "city/backend/amd64/Amd64FunctionTranslator.h"
#include "city/JIT.h"
#include "city/container/StackAllocationContainer.h"

#include "city/backend/amd64/instruction/arithmetic/Amd64Add.h"
#include "city/backend/amd64/instruction/arithmetic/Amd64Div.h"
#include "city/backend/amd64/instruction/arithmetic/Amd64Mul.h"
#include "city/backend/amd64/instruction/arithmetic/Amd64Sub.h"
#include "city/backend/amd64/instruction/control/Amd64Call.h"
#include "city/backend/amd64/instruction/control/Amd64Leave.h"
#include "city/backend/amd64/instruction/control/Amd64Ret.h"
#include "city/backend/amd64/instruction/memory/Amd64Lea.h"
#include "city/backend/amd64/instruction/memory/Amd64Mov.h"
#include "city/backend/amd64/instruction/memory/Amd64Push.h"

using namespace city;

std::span<Register *> Amd64FunctionTranslator::GetScratchRegisterBank(NativeType type)
{
    if (type == NativeType::Integer)
    {
        return std::span{this->reg_.r_volatile};
    }
    else if (type == NativeType::FloatingPoint)
    {
        return std::span{this->reg_.xmm_volatile};
    }

    throw std::runtime_error("unknown type");
}

std::tuple<Register &, Amd64Access, std::optional<std::int32_t>> Amd64FunctionTranslator::LoadValueRM(Value &value)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot load uninstantiated value!");
    }

    auto container = value.GetContainer();

    if (container->GetType() == ContainerType::Stack)
    {
        auto stack_container = dynamic_cast<StackAllocationContainer *>(container);

        return {
                this->reg_.r[5],
                Amd64Access::DisplacedPointer,
                stack_container->GetOffset() * -1 - stack_container->GetSize(),
        };
    }
    else
    {
        return {this->LoadValueR(value), Amd64Access::Value, std::nullopt};
    }
}

void Amd64FunctionTranslator::TranslateInstruction(AddInst &inst)
{
    this->TranslateBinaryInstruction<AddInst, Amd64Add>(inst);
}

void Amd64FunctionTranslator::TranslateInstruction(DivInst &inst)
{
    this->TranslateBinaryInstruction<DivInst, Amd64Div>(inst);
}

void Amd64FunctionTranslator::TranslateInstruction(MulInst &inst)
{
    this->TranslateBinaryInstruction<MulInst, Amd64Mul>(inst);
}

void Amd64FunctionTranslator::TranslateInstruction(SubInst &inst)
{
    this->TranslateBinaryInstruction<SubInst, Amd64Sub>(inst);
}

void Amd64FunctionTranslator::TranslateInstruction(CallInst &inst)
{
    this->PersistScratchRegisters();

    // Load arguments
    auto const &args = inst.GetArguments();
    for (int i = 0; i < args.size(); i++)
    {
        auto value = args[i];
        auto const &value_type = value->GetType();

        if (value_type.GetNativeType() == NativeType::Integer)
        {
            (void)this->LoadValueR(*this->reg_.r_args[i], *value);
        }
        else if (value_type.GetNativeType() == NativeType::FloatingPoint)
        {
            (void)this->LoadValueR(*this->reg_.xmm_args[i], *value);
        }
    }

    // Make call (via RAX)
    auto &addr = this->CopyValueR(this->reg_.r[0], *inst.GetTarget());
    this->Insert(Amd64Call::M(addr));

    // Instantiate retval
    auto native_type = inst.GetType().GetNativeType();
    if (native_type == NativeType::Integer)
    {
        this->reg_.r[0].InstantiateValue(&inst);
    }
    else if (native_type == NativeType::FloatingPoint)
    {
        this->reg_.xmm[0].InstantiateValue(&inst);
    }
}

void Amd64FunctionTranslator::TranslateInstruction(RetInst &inst)
{
    auto retval = inst.GetReturnValue();
    if (retval && retval->IsInstantiated())
    {
        auto native_type = inst.GetType().GetNativeType();
        if (native_type == NativeType::Integer)
        {
            (void)this->LoadValueR(this->reg_.r[0], *retval);
        }
        else if (native_type == NativeType::FloatingPoint)
        {
            (void)this->LoadValueR(this->reg_.xmm[0], *retval);
        }
    }

    if (this->stack_depth_ > 0)
    {
        this->Insert(Amd64Leave::ZO());
    }

    this->Insert(Amd64Ret::ZONear());
}

void Amd64FunctionTranslator::Load(Register &dst, ConstantDataContainer &src)
{
    auto value_type = src.GetValue()->GetType();
    if (value_type.GetNativeType() == NativeType::Integer)
    {
        this->Insert(Amd64Mov::OI(dst, src.GetDataBuffer()));

        if (value_type.IsSigned())
        {
            this->Insert(Amd64Mov::RMSX(dst, dst, value_type.GetSize()));
        }
    }
    else if (value_type.GetNativeType() == NativeType::FloatingPoint)
    {
        auto &valtmp = this->AcquireScratchRegister(NativeType::Integer);

        this->Insert(Amd64Mov::OI(valtmp, src.GetDataBuffer()));
        this->Insert(Amd64Mov::ADQ(dst, valtmp, value_type.GetSize()));
    }
}

void Amd64FunctionTranslator::Load(Register &dst, StackAllocationContainer &src)
{
    auto &rbp = this->reg_.r[5];

    auto value = src.GetValue();
    if (dst.GetValueType() == RegisterType::Integer)
    {
        if (value->GetType().IsSigned())
        {
            this->Insert(Amd64Mov::RMSX(dst, rbp, src.GetSize(), Amd64Access::DisplacedPointer, src.GetOffset() * -1 - src.GetSize()));
        }
        else
        {
            this->Insert(Amd64Mov::RM(dst, rbp, src.GetSize(), Amd64Access::DisplacedPointer, src.GetOffset() * -1 - src.GetSize()));
        }
    }
    else if (dst.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(Amd64Mov::ADQ(dst, rbp, src.GetSize(), Amd64Access::DisplacedPointer, src.GetOffset() * -1 - src.GetSize()));
    }
}

void Amd64FunctionTranslator::Load(Register &dst, StubContainer &src)
{
    auto value = src.GetValue();

    auto const &name = value->GetName();
    if (!name.has_value())
    {
        throw std::runtime_error("cannot link against anonymous value");
    }

    auto index = static_cast<std::int32_t>(this->GetStubIndex(*name));

    (void)this->CopyValueR(dst, this->stub_base_pointer_);
    this->Insert(Amd64Mov::RM(dst, dst, 8, Amd64Access::DisplacedPointer, -8 * (index + 1)));
}

void Amd64FunctionTranslator::Load(Register &dst, Register &src)
{
    // Return if attempt to load into the same register.
    if (dst.GetCode() == src.GetCode())
    {
        return;
    }

    if (dst.GetValueType() == RegisterType::Integer)
    {
        this->Insert(Amd64Mov::RM(dst, src));
    }
    else if (dst.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(Amd64Mov::CS(dst, src));
    }
}

void Amd64FunctionTranslator::Store(StackAllocationContainer &dst, Register &src)
{
    auto &rbp = this->reg_.r[5];

    if (src.GetValueType() == RegisterType::Integer)
    {
        this->Insert(Amd64Mov::MR(rbp, src, dst.GetSize(), Amd64Access::DisplacedPointer, dst.GetOffset() * -1 - dst.GetSize()));
    }
    else if (src.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(Amd64Mov::CS(rbp, src, dst.GetSize(), Amd64Access::DisplacedPointer, dst.GetOffset() * -1 - dst.GetSize()));
    }
}

void Amd64FunctionTranslator::Store(Register &dst, Register &src)
{
    this->Load(dst, src);
}

void Amd64FunctionTranslator::Insert(Amd64Instruction &&inst)
{
    this->module_.pc_ += inst.GetBinarySize();
    this->function.text_.push_back(std::move(inst));
}

void Amd64FunctionTranslator::InsertProlog(Amd64Instruction &&inst)
{
    this->module_.pc_ += inst.GetBinarySize();
    this->function.prolog_.push_back(std::move(inst));
}

Amd64FunctionTranslator::Amd64FunctionTranslator(NativeModule &module, IRFunction &ir_function) : IRTranslator(module, ir_function), function(ir_function)
{
    // Instantiate arguments
    auto const &arg_values = this->ir_function_.GetArgumentValues();
    for (int i = 0; i < arg_values.size(); i++)
    {
        auto value = arg_values[i];
        auto const &value_type = value->GetType();

        if (value_type.GetNativeType() == NativeType::Integer)
        {
            this->reg_.r_args[i]->InstantiateValue(value);

            // Sign extend integer arguments that are used
            if (value_type.IsSigned() && value_type.GetSize() < 8 && value->IsUsed())
            {
                this->Insert(Amd64Mov::RMSX(*this->reg_.r_args[i], *this->reg_.r_args[i], value_type.GetSize()));
            }
        }
        else if (value_type.GetNativeType() == NativeType::FloatingPoint)
        {
            this->reg_.xmm_args[i]->InstantiateValue(value);
        }
    }

    // Save stub location
    this->stub_base_pointer_.IncrementReadCount();
    auto &stub_base_reg = this->AcquireScratchRegister(this->reg_.r[11]);
    this->InsertProlog(Amd64Lea::RM(stub_base_reg, this->reg_.r[5], Amd64Access::Pointer, (-1 * this->module_.pc_) - 7)); // Magic number 7 is the size of instruction plus disp
    stub_base_reg.InstantiateValue(&this->stub_base_pointer_);

    // Function Body
    this->TranslateAllIRBlocks();

    // Stack management
    if (this->stack_depth_ > 0)
    {
        this->InsertProlog(Amd64Push::O(this->reg_.r[5]));
        this->InsertProlog(Amd64Mov::MR(this->reg_.r[5], this->reg_.r[4]));
        this->InsertProlog(Amd64Sub::MI(this->reg_.r[4], this->stack_depth_));
    }
}
