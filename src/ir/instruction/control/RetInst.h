#ifndef CITY_RETINST_H
#define CITY_RETINST_H

#include "ir/instruction/IRInstruction.h"

namespace city
{
    class IRTranslationInterface;
    
    class RetInst : public IRInstruction
    {
        Value *value_;

    public:
        void Apply(IRTranslationInterface *interface) override;

        RetInst(Value *value);
    };
} // namespace city

#endif // CITY_RETINST_H
