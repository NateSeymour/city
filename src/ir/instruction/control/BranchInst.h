#ifndef CITY_BRANCHINST_H
#define CITY_BRANCHINST_H

#include "ir/instruction/Instruction.h"

namespace city
{
    class BranchInst : public Instruction
    {
        Instruction *target_;
    };
} // city

#endif //CITY_BRANCHINST_H
