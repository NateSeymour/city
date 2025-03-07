#include "city/backend/aarch64/AArch64FunctionTranslator.h"

#include <algorithm>
#include <stdexcept>

#include "city/backend/aarch64/instruction/arithmetic/AArch64Add.h"
#include "city/backend/aarch64/instruction/arithmetic/AArch64Cmp.h"
#include "city/backend/aarch64/instruction/arithmetic/AArch64Div.h"
#include "city/backend/aarch64/instruction/arithmetic/AArch64Mul.h"
#include "city/backend/aarch64/instruction/arithmetic/AArch64Sub.h"
#include "city/backend/aarch64/instruction/arithmetic/AArch64Sxt.h"
#include "city/backend/aarch64/instruction/control/AArch64B.h"
#include "city/backend/aarch64/instruction/control/AArch64Ret.h"
#include "city/backend/aarch64/instruction/memory/AArch64Adr.h"
#include "city/backend/aarch64/instruction/memory/AArch64Ldr.h"
#include "city/backend/aarch64/instruction/memory/AArch64Mov.h"
#include "city/backend/aarch64/instruction/memory/AArch64Str.h"

#include "city/ir/block/IRConditionalBlock.h"

using namespace city;

std::span<Register *> AArch64FunctionTranslator::GetScratchRegisterBank(NativeType type)
{
    if (type == NativeType::Integer)
    {
        return std::span{this->reg_.r_volatile};
    }
    else if (type == NativeType::FloatingPoint)
    {
        return std::span{this->reg_.v_volatile};
    }

    throw std::runtime_error("unknown type");
}

void AArch64FunctionTranslator::ProcessCondition(IRConditionalBlock &block)
{
    auto &lhstmp = this->LoadValueR(*block.GetLHS());
    auto &rhstmp = this->LoadValueR(*block.GetRHS());

    this->Insert(AArch64Cmp::R(lhstmp, rhstmp));
    this->Insert(AArch64B::I(1, AArch64ConditionTranslationMap.at(block.GetCondition())));
}

void AArch64FunctionTranslator::TranslateInstruction(AddInst &inst)
{
    this->TranslateBinaryInstruction<AddInst, AArch64Add>(inst);
}

void AArch64FunctionTranslator::TranslateInstruction(DivInst &inst)
{
    this->TranslateBinaryInstruction<DivInst, AArch64Div>(inst);
}

void AArch64FunctionTranslator::TranslateInstruction(MulInst &inst)
{
    this->TranslateBinaryInstruction<MulInst, AArch64Mul>(inst);
}

void AArch64FunctionTranslator::TranslateInstruction(SubInst &inst)
{
    this->TranslateBinaryInstruction<SubInst, AArch64Sub>(inst);
}

void AArch64FunctionTranslator::TranslateInstruction(CallInst &inst)
{
    // Scratch Registers
    this->PersistScratchRegisters();

    // Frame in prolog
    if (!this->frame_.IsInstantiated())
    {
        auto &frame_container = this->AcquireStackSpace(this->frame_.GetType());
        frame_container.InstantiateValue(&this->frame_);
    }

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
            container->Load(*this, *this->reg_.v_args[i]);
        }
    }

    // Make call
    auto &addr = this->reg_.r[14];
    inst.GetTarget()->GetContainer()->Load(*this, addr);
    this->Insert(AArch64B::R(addr, true));

    // Instantiate return value
    if (inst.GetType().GetNativeType() == NativeType::Integer)
    {
        this->reg_.r[0].InstantiateValue(&inst);
    }
    else if (inst.GetType().GetNativeType() == NativeType::FloatingPoint)
    {
        this->reg_.v[0].InstantiateValue(&inst);
    }
}

void AArch64FunctionTranslator::TranslateInstruction(RetInst &inst)
{
    auto retval = inst.GetReturnValue();
    if (retval && retval->IsInstantiated())
    {
        auto type = retval->GetType().GetNativeType();
        auto container = retval->GetContainer();
        if (type == NativeType::Integer)
        {
            container->Load(*this, this->reg_.r[0]);
        }
        else if (type == NativeType::FloatingPoint)
        {
            container->Load(*this, this->reg_.v[0]);
        }
    }

    // Restore frame
    if (this->frame_.IsInstantiated())
    {
        auto container = dynamic_cast<StackAllocationContainer *>(this->frame_.GetContainer());
        this->Insert(AArch64Ldr::P(this->reg_.r[31], container->GetOffset(), this->reg_.r[29], this->reg_.r[30]));
    }

    // Restore stack pointer
    if (this->stack_depth_ > 0)
    {
        this->Insert(AArch64Add::I(this->reg_.r[31], this->reg_.r[31], this->stack_depth_));
    }

    this->Insert(AArch64Ret::Z());
}

void AArch64FunctionTranslator::Load(Register &dst, ConstantDataContainer &src)
{
    auto value_type = src.GetValue()->GetType();

    // Acquire temporary register to load value into
    Register *tmpdst = nullptr;
    if (dst.GetValueType() == RegisterType::Integer)
    {
        tmpdst = &dst;
    }
    else if (dst.GetValueType() == RegisterType::FloatingPoint)
    {
        tmpdst = &this->AcquireScratchRegister(NativeType::Integer);
    }

    // Load the value 16 bits at a time
    auto buffer = reinterpret_cast<std::uint16_t const *>(src.GetDataBuffer().data());
    this->Insert(AArch64Mov::I(*tmpdst, buffer[0], 0));
    auto buffer_size = std::min(src.GetSize(), static_cast<std::size_t>(8));
    for (int i = 1; i < buffer_size / 2; i++)
    {
        std::uint16_t value = buffer[i];

        if (value == 0)
        {
            continue;
        }

        this->Insert(AArch64Mov::I(*tmpdst, value, i, false));
    }

    if (dst.GetValueType() == RegisterType::Integer && value_type.IsSigned() && buffer_size < 8)
    {
        this->Insert(AArch64Sxt::R(*tmpdst, *tmpdst, buffer_size));
    }
    if (dst.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(AArch64Mov::FR(dst, *tmpdst));
    }
}

void AArch64FunctionTranslator::Load(Register &dst, StackAllocationContainer &src)
{
    auto &sp = this->reg_.r[31];

    if (dst.GetValueType() == RegisterType::Integer)
    {
        this->Insert(AArch64Ldr::I(dst, sp, src.GetOffset(), src.GetSize()));
    }
    else if (dst.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(AArch64Ldr::F(dst, sp, src.GetOffset(), src.GetSize()));
    }
}

void AArch64FunctionTranslator::Load(Register &dst, StubContainer &src)
{
    auto value = src.GetValue();

    auto const &name = value->GetName();
    if (!name.has_value())
    {
        throw std::runtime_error("cannot link against anonymous value");
    }

    auto index = static_cast<std::int32_t>(this->GetStubIndex(*name));

    auto &sbr = this->reg_.r[15];
    this->Insert(AArch64Sub::I(dst, sbr, 8 * (index + 1))); // LDR can only take a positive offset, so we need to do this crap
    this->Insert(AArch64Ldr::I(dst, dst));
}

void AArch64FunctionTranslator::Load(Register &dst, Register &src)
{
    // Return if attempt to load into the same register.
    if (dst.GetCode() == src.GetCode())
    {
        return;
    }

    if (dst.GetValueType() == RegisterType::Integer)
    {
        this->Insert(AArch64Mov::R(dst, src));
    }
    else if (dst.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(AArch64Mov::FR(dst, src));
    }
}

void AArch64FunctionTranslator::Store(StackAllocationContainer &dst, Register &src)
{
    auto &sp = this->reg_.r[31];

    if (src.GetValueType() == RegisterType::Integer)
    {
        this->Insert(AArch64Str::I(src, sp, dst.GetOffset(), dst.GetSize()));
    }
    else if (src.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(AArch64Str::F(src, sp, dst.GetOffset(), dst.GetSize()));
    }
}

void AArch64FunctionTranslator::Store(Register &dst, Register &src)
{
    this->Load(dst, src);
}

void AArch64FunctionTranslator::Insert(AArch64Instruction &&inst)
{
    this->module_.pc_ += 4;
    this->function.text_.push_back(std::move(inst));
}

void AArch64FunctionTranslator::InsertProlog(AArch64Instruction &&inst)
{
    this->module_.pc_ += 4;
    this->function.prolog_.push_back(std::move(inst));
}

AArch64FunctionTranslator::AArch64FunctionTranslator(NativeModule &module, IRFunction &ir_function) : IRTranslator(module, ir_function), function(ir_function)
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
            this->reg_.v_args[i]->InstantiateValue(value);
        }
    }

    this->stub_base_pointer_.IncrementReadCount();
    auto &stub_base_reg = this->reg_.r[15];
    this->InsertProlog(AArch64Adr::I(stub_base_reg, -1 * static_cast<std::int32_t>(this->module_.pc_)));
    stub_base_reg.InstantiateValue(&this->stub_base_pointer_);

    // Function Body
    this->TranslateAllIRBlocks();

    // Generate Prolog
    if (this->stack_depth_ > 0)
    {
        this->InsertProlog(AArch64Sub::I(this->reg_.r[31], this->reg_.r[31], this->stack_depth_));
    }

    if (this->frame_.IsInstantiated())
    {
        auto container = dynamic_cast<StackAllocationContainer *>(this->frame_.GetContainer());
        this->InsertProlog(AArch64Str::P(this->reg_.r[31], container->GetOffset(), this->reg_.r[29], this->reg_.r[30]));
    }
}
