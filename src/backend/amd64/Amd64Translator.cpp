#include "Amd64Translator.h"
#include "backend/amd64/instruction/control/Amd64Ret.h"
#include "backend/amd64/instruction/memory/Amd64Pop.h"

using namespace city;

IRTranslationResult Amd64Translator::Translate(AddInst *instruction) {}

IRTranslationResult Amd64Translator::Translate(BranchInst *instruction) {}

IRTranslationResult Amd64Translator::Translate(RetInst *instruction)
{
    if (instruction->HasReturnValue())
    {
        auto return_value = instruction->GetReturnValue();
    }

    this->module.InsertInstruction(Amd64Pop::O64(Amd64RegisterCode::RBP));
    this->module.InsertInstruction(Amd64Ret::ZONear());

    return {};
}

IRTranslationResult Amd64Translator::Translate(StoreInst *instruction) {}
