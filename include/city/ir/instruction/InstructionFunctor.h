#ifndef INSTRUCTIONFUNCTOR_H
#define INSTRUCTIONFUNCTOR_H

#include "arithmetic/AddInst.h"
#include "arithmetic/FAddInst.h"
#include "arithmetic/SubInst.h"
#include "control/CallInst.h"
#include "control/RetInst.h"

namespace city
{
    template<typename ResultType>
    struct InstructionFunctor
    {
        virtual ResultType Translate(AddInst *instruction) = 0;
        virtual ResultType Translate(FAddInst *instruction) = 0;
        virtual ResultType Translate(SubInst *instruction) = 0;
        virtual ResultType Translate(CallInst *instruction) = 0;
        virtual ResultType Translate(RetInst *instruction) = 0;

        virtual ~InstructionFunctor() = default;
    };
} // namespace city

#endif // INSTRUCTIONFUNCTOR_H
