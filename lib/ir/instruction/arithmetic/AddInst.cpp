#include <city/backend/IRTranslator.h>
#include <city/ir/instruction/arithmetic/AddInst.h>

using namespace city;

void AddInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

AddInst::AddInst(Value *return_value, Value *lhs, Value *rhs) : IRBinaryInstruction(return_value, lhs, rhs) {}
