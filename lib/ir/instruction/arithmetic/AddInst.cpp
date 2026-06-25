#include <city/ir/instruction/arithmetic/AddInst.h>
#include <city/transform/IRTranslator.h>

using namespace city;

void AddInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

AddInst::AddInst(Type type, Value *lhs, Value *rhs) : IRBinaryInstruction(type, lhs, rhs) {}
