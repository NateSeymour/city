#include <city/ir/instruction/IRBinaryInstruction.h>

using namespace city;

Value *IRBinaryInstruction::GetLHS() const noexcept
{
    return this->lhs_;
}

Value *IRBinaryInstruction::GetRHS() const noexcept
{
    return this->rhs_;
}

IRBinaryInstruction::IRBinaryInstruction(Type type, Value *lhs, Value *rhs) : IRInstruction(type), lhs_(lhs), rhs_(rhs)
{
    lhs->IncrementReadCount();
    rhs->IncrementReadCount();
}
