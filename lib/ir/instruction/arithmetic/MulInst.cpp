#include <city/ir/instruction/arithmetic/MulInst.h>
#include <city/transform/IRTranslator.h>

using namespace city;

void MulInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

MulInst::MulInst(Type type, Value *lhs, Value *rhs) : IRBinaryInstruction(type, lhs, rhs) {}
