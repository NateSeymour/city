#include "AddInst.h"
#include "backend/IRTranslator.h"

using namespace city;

void AddInst::Apply(IRTranslator *interface)
{
    interface->Translate(this);
}

AddInst::AddInst(Value *return_value, Value *lhs, Value *rhs) : IRBinaryInstruction(return_value, lhs, rhs) {}
