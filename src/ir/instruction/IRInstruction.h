#ifndef CITY_INSTRUCTION_H
#define CITY_INSTRUCTION_H

#include "value/Value.h"

namespace city
{
    class IRTranslator;
    class IRBuilder;

    class IRInstruction
    {
        friend class IRBuilder;

        Value *return_value_ = nullptr;

    public:
        virtual void Apply(IRTranslator *interface) = 0;

        [[nodiscard]] Value *GetReturnValue() const;

        IRInstruction(Value *return_value);
        virtual ~IRInstruction() = default;
    };
} // namespace city

#endif // CITY_INSTRUCTION_H
