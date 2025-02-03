#include <city/backend/IRTranslator.h>
#include <city/ir/instruction/arithmetic/SubInst.h>

using namespace city;

void SubInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

SubInst::SubInst(Value *return_value, Value *lhs, Value *rhs) : IRBinaryInstruction(return_value, lhs, rhs) {}
