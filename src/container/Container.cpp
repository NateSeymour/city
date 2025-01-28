
#include "Container.h"

using namespace city;

void Container::AssociateValue(Value *value)
{
    this->value_ = value;
}

void Container::Disassociate()
{
    this->value_ = nullptr;
}

Value *Container::GetValue() const noexcept
{
    return this->value_;
}

bool Container::HasValue() const noexcept
{
    return this->value_;
}
