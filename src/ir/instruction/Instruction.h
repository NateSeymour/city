#ifndef CITY_INSTRUCTION_H
#define CITY_INSTRUCTION_H

#include "ir/value/Value.h"

namespace city
{
    class Builder;

    class Instruction
    {
        friend class Builder;

        Value *return_value_ = nullptr;

    protected:
        void SetReturnValue(Value *return_value);

    public:
        [[nodiscard]] virtual bool HasReturnValue() const noexcept;
        [[nodiscard]] Value *GetReturnValue();

        virtual ~Instruction() = default;
    };
} // city

#endif //CITY_INSTRUCTION_H
