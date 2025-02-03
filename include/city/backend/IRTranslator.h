#ifndef IRTRANSLATOR_H
#define IRTRANSLATOR_H

#include <city/ir/instruction/arithmetic/AddInst.h>
#include <city/ir/instruction/arithmetic/FAddInst.h>
#include <city/ir/instruction/arithmetic/SubInst.h>
#include <city/ir/instruction/control/CallInst.h>
#include <city/ir/instruction/control/RetInst.h>

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
