#ifndef X86_64TRANSLATIONINTERFACE_H
#define X86_64TRANSLATIONINTERFACE_H

#include "backend/IRTranslationInterface.h"

namespace city
{
    struct x86TranslationInterface : IRTranslationInterface
    {
        IRTranslationResult Translate(AddInst *instruction) override;
        IRTranslationResult Translate(BranchInst *instruction) override;
        IRTranslationResult Translate(RetInst *instruction) override;
        IRTranslationResult Translate(StoreInst *instruction) override;

        explicit x86TranslationInterface(Object &object) : IRTranslationInterface(object) {}
    };
} // namespace city

#endif // X86_64TRANSLATIONINTERFACE_H
