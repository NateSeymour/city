#ifndef CITY_RETINST_H
#define CITY_RETINST_H

#include "ir/instruction/Instruction.h"

namespace city
{
    class RetInst : public Instruction
    {
        Value *value_;

    public:
        RetInst(Value *value);
    };
} // city

#endif //CITY_RETINST_H
