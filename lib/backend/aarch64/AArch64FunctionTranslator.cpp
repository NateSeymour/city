#include "city/backend/aarch64/AArch64FunctionTranslator.h"

#include <algorithm>
#include <stdexcept>

#include "city/backend/aarch64/instruction/arithmetic/AArch64Add.h"
#include "city/backend/aarch64/instruction/arithmetic/AArch64Div.h"
#include "city/backend/aarch64/instruction/arithmetic/AArch64Mul.h"
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

AArch64BinaryOperation AArch64FunctionTranslator::PrepareBinaryOperation(IRBinaryInstruction &inst)
{
    auto optype = inst.GetType().GetNativeType();

    auto &lhs = *inst.GetLHS();
    auto &rhs = *inst.GetRHS();

    std::size_t opsize = inst.GetType().GetSize();

    auto &src1tmp = this->LoadValue(lhs);
    auto &src2tmp = this->LoadValue(rhs);

    Register *dst = nullptr;
    if (lhs.GetReadCount() == 1)
    {
        dst = &src1tmp;
    }
    else if (rhs.GetReadCount() == 1)
    {
        dst = &src2tmp;
    }
    else
    {
        dst = &this->AcquireScratchRegister(optype);
    }

    return {
            .inst = inst,
            .dst = *dst,
            .src1 = src1tmp,
            .src2 = src2tmp,
            .opsize = opsize,
            .optype = optype,
    };
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

void AArch64FunctionTranslator::TranslateInstruction(SubInst &inst) {}
void AArch64FunctionTranslator::TranslateInstruction(CallInst &inst) {}

void AArch64FunctionTranslator::TranslateInstruction(RetInst &inst)
{
    this->Insert(AArch64Ret::Z());
}

void AArch64FunctionTranslator::Load(Register &dst, ConstantDataContainer &src)
{
    if (src.GetSize() > 8)
    {
        throw std::runtime_error("value is too big");
    }

    Register *tmpdst = nullptr;
    if (dst.GetValueType() == RegisterType::Integer)
    {
        tmpdst = &dst;
    }
    else if (dst.GetValueType() == RegisterType::FloatingPoint)
    {
        tmpdst = &this->AcquireScratchRegister(NativeType::Integer);
    }

    auto buffer = reinterpret_cast<std::uint16_t const *>(src.GetDataBuffer().data());
    this->Insert(AArch64Mov::IS(*tmpdst, buffer[0], 0));
    auto buffer_size = src.GetSize();
    for (int i = 1; i < buffer_size / 2; i++)
    {
        std::uint16_t value = buffer[i];

        if (value == 0)
        {
            continue;
        }

        this->Insert(AArch64Mov::KIS(*tmpdst, value, i));
    }

    if (dst.GetValueType() == RegisterType::FloatingPoint)
    {
        this->Insert(AArch64Mov::FR(dst, *tmpdst));
    }
}

void AArch64FunctionTranslator::Load(Register &dst, StackAllocationContainer &src) {}
void AArch64FunctionTranslator::Load(Register &dst, Register &src) {}

Register &AArch64FunctionTranslator::LoadValue(Value &value)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot load uninstantiated value!");
    }

    auto container = value.GetContainer();

    // The value is already loaded, so return itself.
    if (container->GetType() == ContainerType::Register)
    {
        return *dynamic_cast<Register *>(container);
    }

    // Value not loaded
    auto &reg = this->AcquireScratchRegister(value.GetType().GetNativeType());

    container->Load(*this, reg);
    reg.TakeValue(container);

    return reg;
}

void AArch64FunctionTranslator::Store(StackAllocationContainer &dst, Register &src) {}
void AArch64FunctionTranslator::Store(Register &dst, Register &src) {}

void AArch64FunctionTranslator::Insert(AArch64Instruction &&inst)
{
    this->function.text_.push_back(std::move(inst));
}

void AArch64FunctionTranslator::InsertProlog(AArch64Instruction &&inst)
{
    this->function.prolog_.push_back(std::move(inst));
}

AArch64FunctionTranslator::AArch64FunctionTranslator(AArch64Module &module, IRFunction &ir_function) : module_(module), ir_function_(ir_function), function(ir_function)
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

    // Function Body
    for (auto &block : this->ir_function_.GetBlocks())
    {
        for (auto &instruction : block.GetInstructions())
        {
            instruction->Apply(this);
        }
    }

    /*
     * Entering into a function
     * 1. Push RBP. This will save the old stack from.
     * 2. Save RSP -> RBP. This will initialize the stack frame pointer to use for constant offsets into the stack.
     * 3. Subtract space for stack storage from RSP.
     */
    // Generate Prolog
    if (this->stack_depth_ > 0)
    {
        this->AlignStack(16);
    }
}
