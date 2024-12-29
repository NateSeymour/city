#include "AddInst.h"
#include "backend/IRTranslator.h"

using namespace city;

void AddInst::Apply(IRTranslator *interface)
{
    interface->Translate(this);
}

bool AddInst::HasReturnValue() const noexcept
{
    return true;
}

AddInst::AddInst(Value *lhs, Value *rhs) : lhs_(lhs), rhs_(rhs) {}
