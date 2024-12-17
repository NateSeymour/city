#include "BranchInst.h"

using namespace city;

void BranchInst::Apply(IRTranslationInterface *interface)
{
    interface->Translate(this);
}

BranchInst::BranchInst(IRInstruction *target) : target_(target) {}
