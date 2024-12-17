#include "StoreInst.h"

using namespace city;

void StoreInst::Apply(IRTranslationInterface *interface)
{
    interface->Translate(this);
}

StoreInst::StoreInst(Value *dst, Value *src) : dst_(dst), src_(src) {}
