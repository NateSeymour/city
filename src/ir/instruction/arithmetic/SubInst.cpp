#include "SubInst.h"

#include "backend/IRTranslator.h"

using namespace city;

void SubInst::Apply(IRTranslator *interface)
{
    interface->Translate(this);
}

SubInst::SubInst(Value *return_value, Value *lhs, Value *rhs) : IRBinaryInstruction(return_value, lhs, rhs) {}
