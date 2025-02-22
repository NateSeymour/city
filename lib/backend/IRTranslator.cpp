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

RegisterGuard IRTranslator::AcquireScratchRegister(NativeType type)
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

RegisterGuard IRTranslator::AcquireScratchRegister(Register &reg)
{
    RegisterGuard guard{reg};

    if (reg.HasValue())
    {
        auto value = reg.GetValue();
        RegisterGuard new_reg = this->AcquireScratchRegister(value->GetType().GetNativeType());

        reg.Load(*this, new_reg.reg);
        new_reg.reg.TakeValue(&reg);
    }

    return std::move(guard);
}

RegisterGuard IRTranslator::LoadValueR(Value &value)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot load uninstantiated value!");
    }

    auto container = value.GetContainer();

    // The value is already loaded, so return itself.
    if (container->GetType() == ContainerType::Register)
    {
        return {*dynamic_cast<Register *>(container)};
    }
    // The value is constant and cannot be moved.
    else if (container->GetType() == ContainerType::Constant)
    {
        return std::move(this->CopyValueR(value));
    }

    // Value not loaded
    auto guard = this->AcquireScratchRegister(value.GetType().GetNativeType());
    container->Load(*this, guard.reg);
    guard.reg.TakeValue(container);

    return std::move(guard);
}

RegisterGuard IRTranslator::LoadValueR(RegisterGuard dst, Value &value)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot load uninstantiated value!");
    }

    auto container = value.GetContainer();

    // The value is constant and cannot be moved.
    if (container->GetType() == ContainerType::Constant)
    {
        return std::move(this->CopyValueR(std::move(dst), value));
    }

    // Value not loaded
    container->Load(*this, dst.reg);
    dst.reg.TakeValue(container);

    return std::move(dst);
}

RegisterGuard IRTranslator::CopyValueR(Value &value)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot copy uninstantiated value!");
    }

    auto container = value.GetContainer();

    // Value not loaded
    auto guard = this->AcquireScratchRegister(value.GetType().GetNativeType());
    container->Load(*this, guard.reg);

    return std::move(guard);
}

RegisterGuard IRTranslator::CopyValueR(RegisterGuard dst, Value &value)
{
    if (!value.IsInstantiated())
    {
        throw std::runtime_error("cannot copy uninstantiated value!");
    }

    auto container = value.GetContainer();

    // Value not loaded
    container->Load(*this, dst.reg);

    return std::move(dst);
}

void IRTranslator::MoveValue(Container &dst, Value &value)
{
    auto guard = this->LoadValueR(value);

    dst.Store(*this, guard.reg);
    dst.TakeValue(value.GetContainer());
}

std::size_t IRTranslator::GetStubIndex(std::string const &name) const
{
    this->module_.stubs_.push_back(name);

    return this->module_.stubs_.size() - 1;
}

IRTranslator::IRTranslator(NativeModule &module, IRFunction &ir_function) : module_(module), ir_function_(ir_function) {}
