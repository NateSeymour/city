#include <city/backend/NativeInstruction.h>

using namespace city;

void NativeInstruction::SetLabel(std::string name)
{
    this->label_ = std::move(name);
}

bool NativeInstruction::HasLabel() const noexcept
{
    return this->label_.has_value();
}

std::string const &NativeInstruction::GetLabel() const noexcept
{
    return *this->label_;
}

void NativeInstruction::SetStub(Stub stub)
{
    this->stub_ = std::move(stub);
}

bool NativeInstruction::HasStub() const noexcept
{
    return this->stub_.has_value();
}

Stub const &NativeInstruction::GetStub() const
{
    return *this->stub_;
}
