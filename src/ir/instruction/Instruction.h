#ifndef CITY_INSTRUCTION_H
#define CITY_INSTRUCTION_H

#include "backend/IRTranslationInterface.h"
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
        virtual void Apply(IRTranslationInterface *interface) = 0;

        [[nodiscard]] virtual bool HasReturnValue() const noexcept;
        [[nodiscard]] Value *GetReturnValue();

        virtual ~Instruction() = default;
    };
} // namespace city

#endif // CITY_INSTRUCTION_H
