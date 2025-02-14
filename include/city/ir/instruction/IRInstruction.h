#ifndef CITY_INSTRUCTION_H
#define CITY_INSTRUCTION_H

#include "city/value/Value.h"

namespace city
{
    class IRTranslator;
    class IRBuilder;

    class IRInstruction : public Value
    {
        friend class IRBuilder;

    public:
        virtual void Apply(IRTranslator *interface) = 0;

        IRInstruction(Type type);
    };
} // namespace city

#endif // CITY_INSTRUCTION_H
