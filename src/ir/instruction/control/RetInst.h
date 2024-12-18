#ifndef CITY_RETINST_H
#define CITY_RETINST_H

#include "ir/instruction/IRInstruction.h"

namespace city
{
    class IRTranslationInterface;
    class x86TranslationInterface;

    class RetInst : public IRInstruction
    {
        friend class x86TranslationInterface;
        
    protected:
        Value *value_ = nullptr;

    public:
        void Apply(IRTranslationInterface *interface) override;

        RetInst(Value *value);
    };
} // namespace city

#endif // CITY_RETINST_H
