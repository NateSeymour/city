#include "city/backend/IRTranslator.h"
#include <stdexcept>

#include "city/ir/block/IRConditionalBlock.h"

using namespace city;

void IRTranslator::AlignStack(unsigned int alignment) noexcept
{
    this->stack_depth_ += this->stack_depth_ % alignment;
}

StackAllocationContainer &IRTranslator::AcquireStackSpace(Type type)
{
    auto size = type.GetSize();
    auto &container = this->stack_.emplace_back(std::make_unique<StackAllocationContainer>(size));

    container->SetOffset(this->stack_depth_);

    this->stack_depth_ += size;
    this->AlignStack(16);

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

    Register *last_unlocked_register = nullptr;

    // Find an unused register and return it
    for (auto reg : bank)
    {
        if (!reg->IsLocked() && !reg->HasValue() && reg->GetRegisterPurpose() == RegisterPurpose::General)
        {
            return {*reg};
        }

        if (!reg->IsLocked())
        {
            last_unlocked_register = reg;
        }
    }

    // All gp registers are in use. Put something on the stack.
    if (last_unlocked_register == nullptr)
    {
        throw std::runtime_error("All registers are in use for operation! Did you forget to unlock any?");
    }

    auto victim = last_unlocked_register;
    auto &swap = this->AcquireStackSpace(victim->GetValue()->GetType());

    swap.Store(*this, *victim);
    swap.TakeValue(victim);

    return {*victim};
}

Register &IRTranslator::AcquireScratchRegister(Register &reg)
{
    if (reg.HasValue())
    {
        auto value = reg.GetValue();
        auto &new_reg = this->AcquireScratchRegister(value->GetType().GetNativeType());

        reg.Load(*this, new_reg);
        new_reg.TakeValue(&reg);
    }

    return reg;
}

Register &IRTranslator::LoadValueR(Value &value)
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
    // The value is constant and cannot be moved.
    else if (container->GetType() == ContainerType::Constant)
    {
        return this->CopyValueR(value);
    }

    // Value not loaded
    auto &dst = this->AcquireScratchRegister(value.GetType().GetNativeType());
    container->Load(*this, dst);
    dst.TakeValue(container);

    return dst;
}

Register &IRTranslator::LoadValueR(Register &dst, Value &value)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot load uninstantiated value!");
    }

    auto container = value.GetContainer();

    // The value is constant and cannot be moved.
    if (container->GetType() == ContainerType::Constant)
    {
        return this->CopyValueR(dst, value);
    }

    // Value not loaded
    container->Load(*this, dst);
    dst.TakeValue(container);

    return dst;
}

Register &IRTranslator::CopyValueR(Value &value)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot copy uninstantiated value!");
    }

    auto container = value.GetContainer();

    // Value not loaded
    auto &dst = this->AcquireScratchRegister(value.GetType().GetNativeType());
    container->Load(*this, dst);

    return dst;
}

Register &IRTranslator::CopyValueR(Register &dst, Value &value)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot copy uninstantiated value!");
    }

    auto container = value.GetContainer();

    // Value not loaded
    container->Load(*this, dst);

    return dst;
}

void IRTranslator::MoveValue(Container &dst, Value &value)
{
    auto &tmp = this->LoadValueR(value);

    dst.Store(*this, tmp);
    dst.TakeValue(value.GetContainer());
}

std::size_t IRTranslator::GetStubIndex(std::string const &name) const
{
    if (this->module_.stubs_.contains(name))
    {
        return this->module_.stubs_.at(name);
    }

    std::size_t index = this->module_.stubs_.size();
    this->module_.stubs_[name] = index;

    return index;
}

void IRTranslator::TranslateBlock(IRBlock &block)
{
    this->block_insertion_points_[&block] = this->module_.pc_;

    for (auto &instruction : block.GetInstructions())
    {
        instruction->Apply(this);
    }
}

void IRTranslator::TranslateAllIRBlocks()
{
    auto block = &this->ir_function_.GetFirstBlock();
    do
    {
        block->Apply(*this);
    } while ((block = block->GetSuccessor()));
}

IRTranslator::IRTranslator(NativeModule &module, IRFunction &ir_function) : module_(module), ir_function_(ir_function) {}
