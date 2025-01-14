
#include "Container.h"

using namespace city;

void Container::SetValue(Value *value)
{
    this->value_ = value;
}

Value *Container::GetValue() const noexcept
{
    return this->value_;
}

bool Container::HasValue() const noexcept
{
    return this->value_;
}
