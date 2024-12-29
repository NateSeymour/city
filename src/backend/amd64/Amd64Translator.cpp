#include "Amd64Translator.h"
#include "backend/amd64/instruction/control/Amd64RetZONear.h"
#include "backend/amd64/instruction/memory/Amd64PopO64.h"

using namespace city;

IRTranslationResult Amd64Translator::Translate(AddInst *instruction) {}

IRTranslationResult Amd64Translator::Translate(BranchInst *instruction) {}

IRTranslationResult Amd64Translator::Translate(RetInst *instruction)
{
    if (instruction->HasReturnValue())
    {
        auto return_value = instruction->GetReturnValue();
    }

    this->module.EmplaceInstruction<Amd64PopO64>(Amd64RegisterCode::RBP);
    this->module.EmplaceInstruction<Amd46RetZONear>();

    return {};
}

IRTranslationResult Amd64Translator::Translate(StoreInst *instruction) {}
