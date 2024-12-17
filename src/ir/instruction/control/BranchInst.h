#ifndef CITY_BRANCHINST_H
#define CITY_BRANCHINST_H

#include "backend/IRTranslationInterface.h"
#include "ir/instruction/Instruction.h"

namespace city
{
    class BranchInst : public Instruction
    {
        Instruction *target_;

    public:
        void Apply(IRTranslationInterface *interface) override;

        BranchInst(Instruction *target);
    };
} // namespace city

#endif // CITY_BRANCHINST_H
