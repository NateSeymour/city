#ifndef CITY_ADDINST_H
#define CITY_ADDINST_H

#include "ir/instruction/Instruction.h"

namespace city
{
    class AddInst : public Instruction
    {
        Value *lhs_;
        Value *rhs_;

    public:
        [[nodiscard]] bool HasReturnValue() const noexcept override;

        AddInst(Value *lhs, Value *rhs);
    };
} // city

#endif //CITY_ADDINST_H
