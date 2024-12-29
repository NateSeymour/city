#ifndef CITY_STOREINST_H
#define CITY_STOREINST_H

#include "ir/instruction/IRInstruction.h"

namespace city
{
    class IRTranslator;
    
    class StoreInst : public IRInstruction
    {
        Value *dst_;
        Value *src_;

    public:
        void Apply(IRTranslator *interface) override;

        StoreInst(Value *dst, Value *src);
    };
} // namespace city

#endif // CITY_STOREINST_H
