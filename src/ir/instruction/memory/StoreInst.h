#ifndef CITY_STOREINST_H
#define CITY_STOREINST_H

#include "backend/IRTranslationInterface.h"
#include "ir/instruction/Instruction.h"

namespace city
{
    class StoreInst : public Instruction
    {
        Value *dst_;
        Value *src_;

    public:
        void Apply(IRTranslationInterface *interface) override;

        StoreInst(Value *dst, Value *src);
    };
} // namespace city

#endif // CITY_STOREINST_H
