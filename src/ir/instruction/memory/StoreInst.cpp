#include "StoreInst.h"

using namespace city;

StoreInst::StoreInst(Value *dst, Value *src) : dst_(dst), src_(src) {}
