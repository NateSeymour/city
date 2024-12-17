#include "BranchInst.h"

using namespace city;

void BranchInst::Apply(IRTranslationInterface *interface)
{
    interface->Translate(this);
}

BranchInst::BranchInst(Instruction *target) : target_(target) {}
