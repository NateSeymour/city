#include <city/backend/IRTranslator.h>
#include <city/ir/instruction/arithmetic/SubInst.h>

using namespace city;

void SubInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

SubInst::SubInst(Type type, Value *lhs, Value *rhs) : IRBinaryInstruction(type, lhs, rhs) {}
