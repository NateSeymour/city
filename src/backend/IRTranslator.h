#ifndef IRTRANSLATIONINTERFACE_H
#define IRTRANSLATIONINTERFACE_H

#include "NativeModule.h"
#include "ir/instruction/InstructionFunctor.h"

namespace city
{
    struct IRTranslationResult
    {
    };

    struct IRTranslator : InstructionFunctor<IRTranslationResult>
    {
        NativeModule &module;

        explicit IRTranslator(NativeModule &native_module) : module(native_module) {}
    };
} // namespace city

#endif // IRTRANSLATIONINTERFACE_H
