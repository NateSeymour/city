#ifndef X86_64TRANSLATIONINTERFACE_H
#define X86_64TRANSLATIONINTERFACE_H

#include <array>
#include "Amd64Register.h"
#include "backend/IRTranslator.h"

namespace city
{
    struct Amd64Translator : IRTranslator
    {
        IRTranslationResult Translate(AddInst *instruction) override;
        IRTranslationResult Translate(BranchInst *instruction) override;
        IRTranslationResult Translate(RetInst *instruction) override;
        IRTranslationResult Translate(StoreInst *instruction) override;

        explicit Amd64Translator(NativeModule &object) : IRTranslator(object) {}
    };
} // namespace city

#endif // X86_64TRANSLATIONINTERFACE_H
