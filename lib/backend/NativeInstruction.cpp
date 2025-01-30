#include <city/backend/NativeInstruction.h>

using namespace city;

void NativeInstruction::SetLabel(std::string name)
{
    this->label_ = std::move(name);
}

char const *NativeInstruction::GetLabel() const noexcept
{
    if (this->label_)
    {
        return this->label_->data();
    }

    return nullptr;
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
