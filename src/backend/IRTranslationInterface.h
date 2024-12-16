#ifndef IRTRANSLATIONINTERFACE_H
#define IRTRANSLATIONINTERFACE_H

#include "ir/Object.h"
#include "ir/instruction/arithmetic/AddInst.h"
#include "ir/instruction/control/BranchInst.h"
#include "ir/instruction/control/RetInst.h"
#include "ir/instruction/memory/StoreInst.h"

namespace city
{
    struct IRTranslationResult {};

    struct IRTranslationInterface
    {
        using Result = IRTranslationResult;

        Object &object;

        virtual Result Translate(AddInst &instruction) = 0;
        virtual Result Translate(BranchInst &instruction) = 0;
        virtual Result Translate(RetInst &instruction) = 0;
        virtual Result Translate(StoreInst &instruction) = 0;

        template<typename T>
        Result Translate(T&)
        {
            static_assert(false, "unknown instruction type");
        }

        explicit IRTranslationInterface(Object &object) : object(object) {}
        virtual ~IRTranslationInterface() = default;
    };
} // city

#endif //IRTRANSLATIONINTERFACE_H
