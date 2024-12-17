#include "AddInst.h"
#include "backend/IRTranslationInterface.h"

using namespace city;

void AddInst::Apply(IRTranslationInterface *interface)
{
    interface->Translate(this);
}

bool AddInst::HasReturnValue() const noexcept
{
    return true;
}

AddInst::AddInst(Value *lhs, Value *rhs) : lhs_(lhs), rhs_(rhs) {}
