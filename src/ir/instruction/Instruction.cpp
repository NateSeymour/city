
#include "Instruction.h"

using namespace city;

bool Instruction::HasReturnValue() const noexcept
{
    return false;
}

Value *Instruction::GetReturnValue()
{
    return this->return_value_;
}

void Instruction::SetReturnValue(Value *return_value)
{
    this->return_value_ = return_value;
}
