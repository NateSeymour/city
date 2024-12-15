#ifndef CITY_STOREINST_H
#define CITY_STOREINST_H

#include "ir/instruction/Instruction.h"

namespace city
{
    class StoreInst : public Instruction
    {
        Value *dst_;
        Value *src_;

    public:
        StoreInst(Value *dst, Value *src);
    };
}

#endif //CITY_STOREINST_H
