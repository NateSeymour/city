#ifndef CITY_ADDINST_H
#define CITY_ADDINST_H

#include "ir/instruction/IRInstruction.h"

namespace city
{
    class AddInst : public IRInstruction
    {
        Value *lhs_;
        Value *rhs_;

    public:
        void Apply(IRTranslator *interface) override;

        [[nodiscard]] bool HasReturnValue() const noexcept override;

        AddInst(Value *lhs, Value *rhs);
    };
} // namespace city

#endif // CITY_ADDINST_H
