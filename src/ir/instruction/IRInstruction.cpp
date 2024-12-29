#include "IRInstruction.h"

using namespace city;

bool IRInstruction::HasReturnValue() const noexcept
{
    return false;
}

Value *IRInstruction::GetReturnValue()
{
    return this->return_value_;
}

void IRInstruction::SetReturnValue(Value *return_value)
{
    this->return_value_ = return_value;
}
