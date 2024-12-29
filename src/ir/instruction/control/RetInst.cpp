#include "RetInst.h"
#include "backend/IRTranslator.h"

using namespace city;

void RetInst::Apply(IRTranslator *interface)
{
    interface->Translate(this);
}

RetInst::RetInst(Value *value)
{
    this->SetReturnValue(value);
}
