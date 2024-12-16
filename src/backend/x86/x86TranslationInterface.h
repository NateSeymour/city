#ifndef X86_64TRANSLATIONINTERFACE_H
#define X86_64TRANSLATIONINTERFACE_H

#include "backend/IRTranslationInterface.h"

namespace city
{
    struct x86TranslationInterface : IRTranslationInterface
    {
        Result Translate(AddInst &instruction) override;
        Result Translate(BranchInst &instruction) override;
        Result Translate(RetInst &instruction) override;
        Result Translate(StoreInst &instruction) override;

        explicit x86TranslationInterface(Object &object) : IRTranslationInterface(object) {}
    };
} // namespace city

#endif // X86_64TRANSLATIONINTERFACE_H
