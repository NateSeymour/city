#ifndef IRTRANSLATOR_H
#define IRTRANSLATOR_H

#include <city/ir/instruction/InstructionFunctor.h>

namespace city
{
    struct IRTranslator
    {
        virtual void TranslateInstruction(AddInst &inst) = 0;
        virtual void TranslateInstruction(FAddInst &inst) = 0;
        virtual void TranslateInstruction(SubInst &inst) = 0;
        virtual void TranslateInstruction(CallInst &inst) = 0;
        virtual void TranslateInstruction(RetInst &inst) = 0;

        virtual ~IRTranslator() = default;
    };
} // namespace city

#endif // IRTRANSLATOR_H
