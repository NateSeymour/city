#include <city/ir/instruction/arithmetic/DivInst.h>
#include <city/transform/IRTranslator.h>

using namespace city;

void DivInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

DivInst::DivInst(Type type, Value *lhs, Value *rhs) : IRBinaryInstruction(type, lhs, rhs) {}
