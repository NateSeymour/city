#include "city/backend/aarch64/AArch64FunctionTranslator.h"

#include <algorithm>
#include <stdexcept>

#include "city/backend/aarch64/instruction/arithmetic/AArch64Add.h"
#include "city/backend/aarch64/instruction/arithmetic/AArch64Div.h"
#include "city/backend/aarch64/instruction/arithmetic/AArch64Mul.h"
#include "city/backend/aarch64/instruction/arithmetic/AArch64Sub.h"
#include "city/backend/aarch64/instruction/control/AArch64Ret.h"
#include "city/backend/aarch64/instruction/memory/AArch64Mov.h"

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
    this->PersistScratchRegisters();
}

void AArch64FunctionTranslator::TranslateInstruction(RetInst &inst)
{
    auto retval = inst.GetReturnValue();
    if (retval && retval->IsInstantiated())
    {
        auto type = retval->GetType().GetNativeType();
        if (type == NativeType::Integer)
        {
            retval->GetContainer()->Load(*this, this->reg_.r[0]);
        }
        else if (type == NativeType::FloatingPoint)
        {
            retval->GetContainer()->Load(*this, this->reg_.v[0]);
        }
    }

    if (this->stack_depth_ > 0)
    {
    }

    this->Insert(AArch64Ret::Z());
}

void AArch64FunctionTranslator::Load(Register &dst, ConstantDataContainer &src)
{
    if (src.GetSize() > 8)
    {
        throw std::runtime_error("value is too big");
    }

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
    auto buffer_size = src.GetSize();
    for (int i = 1; i < buffer_size / 2; i++)
    {
        std::uint16_t value = buffer[i];

        if (value == 0)
        {
            continue;
        }

        this->Insert(AArch64Mov::I(*tmpdst, value, i, false));
    }

    // Sign extend if necessary


    if (dst.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(AArch64Mov::FR(dst, *tmpdst));
    }
}

void AArch64FunctionTranslator::Load(Register &dst, StackAllocationContainer &src) {}
void AArch64FunctionTranslator::Load(Register &dst, StubContainer &src) {}
void AArch64FunctionTranslator::Load(Register &dst, Register &src) {}

void AArch64FunctionTranslator::Store(StackAllocationContainer &dst, Register &src) {}
void AArch64FunctionTranslator::Store(Register &dst, Register &src) {}

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
    auto &stub_base_reg = this->AcquireScratchRegister(NativeType::Integer);


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
    }
}
