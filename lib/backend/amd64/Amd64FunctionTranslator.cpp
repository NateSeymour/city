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

        if (!value->IsInstantiated())
        {
            throw std::runtime_error("attempted to pass uninstantiated value");
        }

        auto container = value->GetContainer();
        if (value_type.GetNativeType() == NativeType::Integer)
        {
            container->Load(*this, *this->reg_.r_args[i]);
        }
        else if (value_type.GetNativeType() == NativeType::FloatingPoint)
        {
            container->Load(*this, *this->reg_.xmm_args[i]);
        }
    }

    // Make call
    auto &addr = this->LoadValue(*inst.GetTarget());
    this->Insert(Amd64Call::M64(addr));

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
            this->MoveValue(this->reg_.r[0], *retval);
        }
        else if (native_type == NativeType::FloatingPoint)
        {
            this->MoveValue(this->reg_.xmm[0], *retval);
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
    if (src.GetSize() > 8)
    {
        throw std::runtime_error("value is too big");
    }

    auto value_type = src.GetValue()->GetType();
    if (value_type.GetNativeType() == NativeType::Integer)
    {
        this->Insert(Amd64Mov::OIX(dst, src.GetDataBuffer()));
    }
    // Need to take the roundabout way of loading the value first onto the stack via integer move and then into an xmm register.
    else if (value_type.GetNativeType() == NativeType::FloatingPoint)
    {
        auto &valtmp = this->AcquireScratchRegister(NativeType::Integer);
        auto &stacktmp = this->AcquireStackSpace(value_type);

        this->Insert(Amd64Mov::OIX(valtmp, src.GetDataBuffer()));
        this->Insert(Amd64Mov::MRX(this->reg_.r[5], valtmp, src.GetSize(), Amd64Mod::DisplacedPointer, stacktmp.GetOffset() * -1));
        this->Insert(Amd64Mov::SDA(dst, this->reg_.r[5], Amd64Mod::DisplacedPointer, stacktmp.GetOffset() * -1));
    }
}

void Amd64FunctionTranslator::Load(Register &dst, StackAllocationContainer &src)
{
    auto &rbp = this->reg_.r[5];

    if (dst.GetValueType() == RegisterType::Integer)
    {
        this->Insert(Amd64Mov::RMX(dst, rbp, src.GetSize(), Amd64Mod::DisplacedPointer, src.GetOffset() * -1));
    }
    else if (dst.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(Amd64Mov::SDA(dst, rbp, Amd64Mod::DisplacedPointer, src.GetOffset() * -1));
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

    auto &rip = this->reg_.r[5];
    this->Insert(Amd64Mov::RM64(dst, rip, Amd64Mod::Pointer, (-8 * (index + 1)) - this->module_.pc_ - 7));
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
        this->Insert(Amd64Mov::RM64(dst, src));
    }
    else if (dst.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(Amd64Mov::SDA(dst, src));
    }
}

void Amd64FunctionTranslator::Store(StackAllocationContainer &dst, Register &src)
{
    auto &rbp = this->reg_.r[5];

    if (src.GetValueType() == RegisterType::Integer)
    {
        this->Insert(Amd64Mov::MR64(rbp, src, Amd64Mod::DisplacedPointer, dst.GetOffset() * -1));
    }
    else if (src.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(Amd64Mov::SDA(rbp, src, Amd64Mod::DisplacedPointer, dst.GetOffset() * -1));
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
        }
        else if (value_type.GetNativeType() == NativeType::FloatingPoint)
        {
            this->reg_.xmm_args[i]->InstantiateValue(value);
        }
    }

    // Function Body
    for (auto &block : this->ir_function_.GetBlocks())
    {
        for (auto &instruction : block.GetInstructions())
        {
            instruction->Apply(this);
        }
    }

    // Generate Prolog
    if (this->stack_depth_ > 0)
    {
        this->InsertProlog(Amd64Push::M64(this->reg_.r[5]));
        this->InsertProlog(Amd64Mov::MR64(this->reg_.r[5], this->reg_.r[4]));
        this->InsertProlog(Amd64Sub::MI64(this->reg_.r[4], this->stack_depth_));
    }
}
