#ifndef INSTRUCTIONFUNCTOR_H
#define INSTRUCTIONFUNCTOR_H

#include "arithmetic/AddInst.h"
#include "arithmetic/SubInst.h"
#include "control/CallInst.h"
#include "control/RetInst.h"

namespace city
{
    template<typename ResultType>
    struct InstructionFunctor
    {
        virtual ResultType Translate(AddInst *instruction) = 0;
        virtual ResultType Translate(SubInst *instruction) = 0;
        virtual ResultType Translate(CallInst *instruction) = 0;
        virtual ResultType Translate(RetInst *instruction) = 0;

        template<typename T>
        ResultType Translate(T *)
        {
            static_assert("unknown instruction type");
        }

        virtual ~InstructionFunctor() = default;
    };
} // namespace city

#endif // INSTRUCTIONFUNCTOR_H
