#ifndef INSTRUCTIONFUNCTOR_H
#define INSTRUCTIONFUNCTOR_H

#include "ir/instruction/arithmetic/AddInst.h"
#include "ir/instruction/control/BranchInst.h"
#include "ir/instruction/control/RetInst.h"
#include "ir/instruction/memory/StoreInst.h"

namespace city
{
    template<typename ResultType>
    struct InstructionFunctor
    {
        virtual ResultType Translate(AddInst *instruction) = 0;
        virtual ResultType Translate(BranchInst *instruction) = 0;
        virtual ResultType Translate(RetInst *instruction) = 0;
        virtual ResultType Translate(StoreInst *instruction) = 0;

        template<typename T>
        ResultType Translate(T *)
        {
            static_assert("unknown instruction type");
        }

        virtual ~InstructionFunctor() = default;
    };
} // namespace city

#endif // INSTRUCTIONFUNCTOR_H
