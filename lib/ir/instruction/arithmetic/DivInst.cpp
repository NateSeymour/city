#include <city/backend/IRTranslator.h>
#include <city/ir/instruction/arithmetic/DivInst.h>

using namespace city;

void DivInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

DivInst::DivInst(Type type, Value *lhs, Value *rhs) : IRBinaryInstruction(type, lhs, rhs) {}
