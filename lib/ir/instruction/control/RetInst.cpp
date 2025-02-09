#include <city/backend/IRTranslator.h>
#include <city/ir/instruction/control/RetInst.h>

using namespace city;

void RetInst::Apply(IRTranslator *interface)
{
    interface->TranslateInstruction(*this);
}

RetInst::RetInst(Value *value) : IRInstruction(value->GetType()), return_value_(value)
{
    value->IncrementReadCount();
}
