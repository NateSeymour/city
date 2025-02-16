#include "city/backend/IRTranslator.h"

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
        if (!reg->HasValue())
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

Register &IRTranslator::LoadValue(Value &value)
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
    if (!reg.SetTempValue(&value))
    {
        throw std::runtime_error("failed to set temporary value");
    }

    return reg;
}

void IRTranslator::MoveValue(Container &dst, Value &value)
{
    auto &tmp = this->LoadValue(value);

    dst.Store(*this, tmp);
    dst.TakeValue(value.GetContainer());

    tmp.ClearTempValue();
}

IRTranslator::IRTranslator(IRFunction &ir_function) : ir_function_(ir_function) {}
