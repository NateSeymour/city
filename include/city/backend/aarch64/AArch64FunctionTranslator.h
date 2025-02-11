#ifndef AARCH64FUNCTIONTRANSLATOR_H
#define AARCH64FUNCTIONTRANSLATOR_H

#include "city/backend/IRTranslator.h"

namespace city
{
    class AArch64FunctionTranslator : public IRTranslator
    {
    protected:
        void TranslateInstruction(AddInst &inst) override;
        void TranslateInstruction(DivInst &inst) override;
        void TranslateInstruction(MulInst &inst) override;
        void TranslateInstruction(SubInst &inst) override;
        void TranslateInstruction(CallInst &inst) override;
        void TranslateInstruction(RetInst &inst) override;
    };
} // namespace city

#endif // AARCH64FUNCTIONTRANSLATOR_H
