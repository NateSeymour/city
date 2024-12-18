#include "x86TranslationInterface.h"
#include "backend/x86/instruction/control/Amd64RetZONear.h"
#include "backend/x86/instruction/memory/Amd64PopO64.h"

using namespace city;

IRTranslationResult x86TranslationInterface::Translate(AddInst *instruction) {}

IRTranslationResult x86TranslationInterface::Translate(BranchInst *instruction) {}

IRTranslationResult x86TranslationInterface::Translate(RetInst *instruction)
{
    if (!instruction->value_)
    {
        this->object.EmplaceInstruction<Amd64PopO64>(x86RegisterCode::RBP);
        this->object.EmplaceInstruction<Amd46RetZONear>();
    }
}

IRTranslationResult x86TranslationInterface::Translate(StoreInst *instruction) {}
