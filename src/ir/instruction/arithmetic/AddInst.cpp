#include "AddInst.h"

using namespace city;

bool AddInst::HasReturnValue() const noexcept
{
    return true;
}

AddInst::AddInst(Value *lhs, Value *rhs) : lhs_(lhs), rhs_(rhs) {}
