#ifndef CITY_RETINST_H
#define CITY_RETINST_H

#include "backend/IRTranslationInterface.h"
#include "ir/instruction/Instruction.h"

namespace city
{
    class RetInst : public Instruction
    {
        Value *value_;

    public:
        void Apply(IRTranslationInterface *interface) override;

        RetInst(Value *value);
    };
} // namespace city

#endif // CITY_RETINST_H
