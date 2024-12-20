#ifndef IRTRANSLATIONINTERFACE_H
#define IRTRANSLATIONINTERFACE_H

#include "NativeModule.h"
#include "ir/instruction/InstructionFunctor.h"

namespace city
{
    struct IRTranslationResult
    {
    };

    struct IRTranslationInterface : InstructionFunctor<IRTranslationResult>
    {
        NativeModule &object;

        explicit IRTranslationInterface(NativeModule &object) : object(object) {}
    };
} // namespace city

#endif // IRTRANSLATIONINTERFACE_H
