#include "city/backend/IRTranslator.h"
#include <stdexcept>

using namespace city;

void IRTranslator::AlignStack(unsigned int alignment) noexcept
{
    this->stack_depth_ += this->stack_depth_ % alignment;
}

StackAllocationContainer &IRTranslator::AcquireStackSpace(Type type)
{
    auto size = type.GetSize();
    auto &container = this->stack_.emplace_back(std::make_unique<StackAllocationContainer>(size));

    this->stack_depth_ += size;
    container->SetOffset(this->stack_depth_);

    return *container.get();
}

void IRTranslator::PersistRegisterBank(std::span<Register *> bank)
{
    for (auto reg : bank)
    {
        if (reg->HasValue())
        {
            auto value = reg->GetValue();
            auto &swap = this->AcquireStackSpace(value->GetType());
            this->MoveValue(swap, *value);
        }
    }
}

void IRTranslator::PersistScratchRegisters()
{
    this->PersistRegisterBank(this->GetScratchRegisterBank(NativeType::Integer));
    this->PersistRegisterBank(this->GetScratchRegisterBank(NativeType::FloatingPoint));
}

Register &IRTranslator::AcquireScratchRegister(NativeType type)
{
    auto bank = this->GetScratchRegisterBank(type);

    // Find an unused register and return it
    for (auto reg : bank)
    {
        if (!reg->HasValue() && reg->GetRegisterPurpose() == RegisterPurpose::General)
        {
            return *reg;
        }
    }

    // All gp registers are in use. Put something on the stack.
    auto victim = bank[(++this->register_dislocation_count_) % bank.size()];
    auto &swap = this->AcquireStackSpace(victim->GetValue()->GetType());

    this->Store(swap, *victim);
    swap.TakeValue(victim);

    return *victim;
}

BinaryOperation IRTranslator::PrepareBinaryOperation(IRBinaryInstruction &inst, bool destructive)
{
    auto optype = inst.GetType().GetNativeType();

    auto &lhs = *inst.GetLHS();
    auto &rhs = *inst.GetRHS();

    std::size_t opsize = inst.GetType().GetSize();

    auto &src1tmp = this->LoadValue(lhs, destructive); // Force copy of src1 if the instruction is destructive.
    auto &src2tmp = this->LoadValue(rhs);

    Register *dst = nullptr;
    if (lhs.GetReadCount() == 1 || destructive)
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

Register &IRTranslator::LoadValue(Value &value, bool copy)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot load uninstantiated value!");
    }

    auto container = value.GetContainer();

    // The value is already loaded, so return itself.
    if (container->GetType() == ContainerType::Register && !copy)
    {
        return *dynamic_cast<Register *>(container);
    }

    // Value not loaded
    auto &reg = this->AcquireScratchRegister(value.GetType().GetNativeType());
    if (!((!copy && reg.TakeValue(container)) || reg.SetTempValue(&value)))
    {
        throw std::runtime_error("failed to set temporary value");
    }

    container->Load(*this, reg);

    return reg;
}

std::size_t IRTranslator::GetStubIndex(std::string const &name) const
{
    this->module_.stubs_.push_back(name);

    return this->module_.stubs_.size() - 1;
}

void IRTranslator::MoveValue(Container &dst, Value &value)
{
    auto &tmp = this->LoadValue(value);

    dst.Store(*this, tmp);
    dst.TakeValue(value.GetContainer());

    tmp.ClearTempValue();
}

IRTranslator::IRTranslator(NativeModule &module, IRFunction &ir_function) : module_(module), ir_function_(ir_function) {}
