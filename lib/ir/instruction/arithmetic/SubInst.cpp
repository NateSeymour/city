#include <city/ir/instruction/arithmetic/SubInst.h>
#include <city/transform/IRTranslator.h>

using namespace city;

void SubInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

SubInst::SubInst(Type type, Value *lhs, Value *rhs) : IRBinaryInstruction(type, lhs, rhs) {}
