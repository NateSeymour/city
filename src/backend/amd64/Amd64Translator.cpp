#include "Amd64Translator.h"

using namespace city;

IRTranslationResult Amd64Translator::Translate(AddInst *instruction)
{
    auto lhs = this->builder.MoveValueToUnusedRegister(instruction->GetLHS());
    auto rhs = this->builder.MoveValueToUnusedRegister(instruction->GetRHS());

    this->builder.InsertAddInst(lhs->GetCode(), rhs->GetCode());

    return {};
}

IRTranslationResult Amd64Translator::Translate(BranchInst *instruction) {}

IRTranslationResult Amd64Translator::Translate(RetInst *instruction)
{
    if (instruction->HasReturnValue())
    {
        auto return_value = instruction->GetReturnValue();
        this->builder.MoveValueToRegister(return_value, Amd64RegisterCode::RAX, Amd64RegisterConflictStrategy::Discard);
    }

    this->builder.InsertPopInst(Amd64RegisterCode::RBP);
    this->builder.InsertReturnInst();

    return {};
}

IRTranslationResult Amd64Translator::Translate(StoreInst *instruction) {}
