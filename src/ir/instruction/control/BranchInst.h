#ifndef CITY_BRANCHINST_H
#define CITY_BRANCHINST_H

#include "ir/instruction/IRInstruction.h"

namespace city
{
    class IRTranslator;
    
    class BranchInst : public IRInstruction
    {
        IRInstruction *target_;

    public:
        void Apply(IRTranslator *interface) override;

        BranchInst(IRInstruction *target);
    };
} // namespace city

#endif // CITY_BRANCHINST_H
