#include "city/container/Container.h"
#include "city/value/Value.h"

using namespace city;

bool Container::InstantiateValue(Value *value)
{
    if (this->HasValue() || !value || value->IsInstantiated())
    {
        return false;
    }

    this->temp_ = false;
    this->value_ = value;
    this->value_->container_ = this;

    return true;
}

bool Container::TakeValue(Container *container)
{
    if (this->HasValue() || !container->HasValue())
    {
        return false;
    }

    this->temp_ = false;
    this->value_ = container->value_;
    this->value_->container_ = this;
    container->value_ = nullptr;

    return true;
}

bool Container::HasValue() const noexcept
{
    return this->value_ && this->value_->IsUsed();
}

Value *Container::GetValue() const noexcept
{
    return this->value_;
}

bool Container::SetTempValue(Value *value)
{
    if (this->HasValue())
    {
        return false;
    }

    this->temp_ = true;
    this->value_ = value;

    return true;
}

bool Container::ClearTempValue()
{
    if (!this->temp_)
    {
        return false;
    }

    this->temp_ = false;
    this->value_ = nullptr;
    return true;
}
