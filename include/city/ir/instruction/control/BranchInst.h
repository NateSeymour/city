#ifndef BRANCHINST_H
#define BRANCHINST_H
#include "city/ir/instruction/IRInstruction.h"

namespace city
{
    class IRBlock;

    class BranchInst : public IRInstruction
    {
    public:
        BranchInst(IRBlock &target) : IRInstruction(Type::Get<void>()) {}
    };
} // namespace city

#endif // BRANCHINST_H
