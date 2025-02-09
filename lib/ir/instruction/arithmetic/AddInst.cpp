#include <city/backend/IRTranslator.h>
#include <city/ir/instruction/arithmetic/AddInst.h>

using namespace city;

void AddInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

AddInst::AddInst(Type type, Value *lhs, Value *rhs) : IRBinaryInstruction(type, lhs, rhs) {}
