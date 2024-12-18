#include "BranchInst.h"
#include "backend/IRTranslationInterface.h"

using namespace city;

void BranchInst::Apply(IRTranslationInterface *interface)
{
    interface->Translate(this);
}

BranchInst::BranchInst(IRInstruction *target) : target_(target) {}
