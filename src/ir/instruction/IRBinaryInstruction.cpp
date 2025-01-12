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

IRBinaryInstruction::IRBinaryInstruction(Value *lhs, Value *rhs) : lhs_(lhs), rhs_(rhs) {}
