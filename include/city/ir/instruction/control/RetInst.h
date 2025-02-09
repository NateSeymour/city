#ifndef CITY_RETINST_H
#define CITY_RETINST_H

#include <city/ir/instruction/IRInstruction.h>

namespace city
{
    class IRTranslator;

    class RetInst : public IRInstruction
    {
        Value *return_value_ = nullptr;

    public:
        void Apply(IRTranslator *interface) override;

        [[nodiscard]] Value *GetReturnValue() const noexcept;

        RetInst(Value *value);
    };
} // namespace city

#endif // CITY_RETINST_H
