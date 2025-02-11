#ifndef IRTRANSLATOR_H
#define IRTRANSLATOR_H

#include <city/ir/instruction/arithmetic/AddInst.h>
#include <city/ir/instruction/arithmetic/DivInst.h>
#include <city/ir/instruction/arithmetic/MulInst.h>
#include <city/ir/instruction/arithmetic/SubInst.h>
#include <city/ir/instruction/control/CallInst.h>
#include <city/ir/instruction/control/RetInst.h>

namespace city
{
    class IRTranslator
    {
    protected:
        virtual void TranslateInstruction(AddInst &inst) = 0;
        virtual void TranslateInstruction(DivInst &inst) = 0;
        virtual void TranslateInstruction(MulInst &inst) = 0;
        virtual void TranslateInstruction(SubInst &inst) = 0;
        virtual void TranslateInstruction(CallInst &inst) = 0;
        virtual void TranslateInstruction(RetInst &inst) = 0;

    public:
        virtual ~IRTranslator() = default;
    };
} // namespace city

#endif // IRTRANSLATOR_H
