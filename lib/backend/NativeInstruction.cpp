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

void NativeInstruction::SetLinkerRef(std::string name)
{
    this->linker_ref_ = std::move(name);
}

bool NativeInstruction::HasLinkerRef() const noexcept
{
    return this->linker_ref_.has_value();
}

std::string const &NativeInstruction::GetLinkerRef() const
{
    return *this->linker_ref_;
}
