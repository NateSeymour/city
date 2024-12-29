#include "BranchInst.h"
#include "backend/IRTranslator.h"

using namespace city;

void BranchInst::Apply(IRTranslator *interface)
{
    interface->Translate(this);
}

BranchInst::BranchInst(IRInstruction *target) : target_(target) {}
