#ifndef CITY_RETINST_H
#define CITY_RETINST_H

#include "ir/instruction/IRInstruction.h"

namespace city
{
    class IRTranslator;

    class RetInst : public IRInstruction
    {
    public:
        void Apply(IRTranslator *interface) override;

        RetInst(Value *return_value);
    };
} // namespace city

#endif // CITY_RETINST_H
