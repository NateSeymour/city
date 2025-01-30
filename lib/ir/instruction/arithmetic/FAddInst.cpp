#include <city/backend/IRTranslator.h>
#include <city/ir/instruction/arithmetic/FAddInst.h>

using namespace city;

void FAddInst::Apply(IRTranslator *interface)
{
    interface->Translate(this);
}

FAddInst::FAddInst(Value *return_value, Value *lhs, Value *rhs) : IRBinaryInstruction(return_value, lhs, rhs) {}
