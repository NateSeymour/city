#include <city/backend/IRTranslator.h>
#include <city/ir/instruction/arithmetic/CmpInst.h>

using namespace city;

void CmpInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

CmpInst::CmpInst(Type type, Value *lhs, Value *rhs) : IRBinaryInstruction(type, lhs, rhs) {}
