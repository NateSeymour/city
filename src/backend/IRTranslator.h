#ifndef IRTRANSLATOR_H
#define IRTRANSLATOR_H

#include "ir/instruction/InstructionFunctor.h"

namespace city
{
    struct IRTranslationResult
    {
    };

    struct IRTranslator : InstructionFunctor<IRTranslationResult>
    {
    };
} // namespace city

#endif // IRTRANSLATOR_H
