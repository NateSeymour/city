#include "Amd64Translator.h"

using namespace city;

IRTranslationResult Amd64Translator::Translate(AddInst *instruction) {}

IRTranslationResult Amd64Translator::Translate(BranchInst *instruction) {}

IRTranslationResult Amd64Translator::Translate(RetInst *instruction)
{
    if (instruction->HasReturnValue())
    {
        auto return_value = instruction->GetReturnValue();
        this->builder.MoveValueToRegister(return_value, Amd64RegisterCode::RAX, Amd64RegisterConflictStrategy::Discard);
    }

    this->builder.PopRegister(Amd64RegisterCode::RBP);
    this->builder.Return();

    return {};
}

IRTranslationResult Amd64Translator::Translate(StoreInst *instruction) {}
