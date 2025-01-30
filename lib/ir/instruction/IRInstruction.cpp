#include <city/ir/instruction/IRInstruction.h>

using namespace city;

Value *IRInstruction::GetReturnValue() const
{
    return this->return_value_;
}

IRInstruction::IRInstruction(Value *return_value) : return_value_(return_value) {}
