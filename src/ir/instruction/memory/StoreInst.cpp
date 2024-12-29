#include "StoreInst.h"
#include "backend/IRTranslator.h"

using namespace city;

void StoreInst::Apply(IRTranslator *interface)
{
    interface->Translate(this);
}

StoreInst::StoreInst(Value *dst, Value *src) : dst_(dst), src_(src) {}
