#ifndef X86_64TRANSLATIONINTERFACE_H
#define X86_64TRANSLATIONINTERFACE_H

#include "Amd64Builder.h"
#include "Amd64Module.h"
#include "backend/IRTranslator.h"
#include "ir/instruction/InstructionFunctor.h"

namespace city
{
    struct Amd64Translator : IRTranslator
    {
        Amd64Module &module;
        Amd64Builder builder;

        IRTranslationResult Translate(AddInst *instruction) override;
        IRTranslationResult Translate(BranchInst *instruction) override;
        IRTranslationResult Translate(RetInst *instruction) override;
        IRTranslationResult Translate(StoreInst *instruction) override;

        explicit Amd64Translator(Amd64Module &module) : module(module), builder(module) {}
    };
} // namespace city

#endif // X86_64TRANSLATIONINTERFACE_H
