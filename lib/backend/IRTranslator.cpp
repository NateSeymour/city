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
