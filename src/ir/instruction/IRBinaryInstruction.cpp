#include "IRBinaryInstruction.h"

using namespace city;

Value *IRBinaryInstruction::GetLHS() const noexcept
{
    return this->lhs_;
}

Value *IRBinaryInstruction::GetRHS() const noexcept
{
    return this->rhs_;
}

IRBinaryInstruction::IRBinaryInstruction(Value *return_value, Value *lhs, Value *rhs) : IRInstruction(return_value), lhs_(lhs), rhs_(rhs)
{
    lhs->IncrementReadCount();
    rhs->IncrementReadCount();
}
