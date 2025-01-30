#ifndef CITY_RETINST_H
#define CITY_RETINST_H

#include <city/ir/instruction/IRInstruction.h>

namespace city
{
    class IRTranslator;

    class RetInst : public IRInstruction
    {
    public:
        void Apply(IRTranslator *interface) override;

        RetInst(Value *value);
    };
} // namespace city

#endif // CITY_RETINST_H
