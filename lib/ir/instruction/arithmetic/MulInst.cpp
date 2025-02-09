#include <city/backend/IRTranslator.h>
#include <city/ir/instruction/arithmetic/MulInst.h>

using namespace city;

void MulInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

MulInst::MulInst(Type type, Value *lhs, Value *rhs) : IRBinaryInstruction(type, lhs, rhs) {}
