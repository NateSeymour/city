#ifndef IRTRANSLATIONINTERFACE_H
#define IRTRANSLATIONINTERFACE_H

#include "Object.h"
#include "ir/instruction/InstructionFunctor.h"

namespace city
{
    struct IRTranslationResult
    {
    };

    struct IRTranslationInterface : InstructionFunctor<IRTranslationResult>
    {
        Object &object;

        explicit IRTranslationInterface(Object &object) : object(object) {}
    };
} // namespace city

#endif // IRTRANSLATIONINTERFACE_H
