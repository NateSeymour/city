#ifndef IRBINARYINSTRUCTION_H
#define IRBINARYINSTRUCTION_H

#include "../../Value.h"
#include "IRInstruction.h"

namespace city
{
    class IRBinaryInstruction : public IRInstruction
    {
    protected:
        Value *lhs_;
        Value *rhs_;

    public:
        [[nodiscard]] Value *GetLHS() const noexcept;
        [[nodiscard]] Value *GetRHS() const noexcept;

        IRBinaryInstruction(Value *return_value, Value *lhs, Value *rhs);
    };
} // namespace city

#endif // IRBINARYINSTRUCTION_H
