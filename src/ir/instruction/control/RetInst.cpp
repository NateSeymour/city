#include "RetInst.h"

using namespace city;

void RetInst::Apply(IRTranslationInterface *interface)
{
    interface->Translate(this);
}

RetInst::RetInst(Value *value) : value_(value) {}
