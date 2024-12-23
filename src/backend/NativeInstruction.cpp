#include "NativeInstruction.h"

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
