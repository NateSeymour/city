#include <city/backend/NativeInstruction.h>

using namespace city;

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
