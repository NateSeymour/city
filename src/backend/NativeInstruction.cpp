#include "NativeInstruction.h"

using namespace city;

void NativeInstruction::SetAssociatedSymbolName(std::string name)
{
    this->assoc_symbol_ = std::move(name);
}

char const *NativeInstruction::GetAssociatedSymbolName() const noexcept
{
    if (this->assoc_symbol_)
    {
        return this->assoc_symbol_->data();
    }

    return nullptr;
}
