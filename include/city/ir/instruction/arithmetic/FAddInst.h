#ifndef CITY_FADDINST_H
#define CITY_FADDINST_H

#include <city/ir/instruction/IRBinaryInstruction.h>

namespace city
{
    class FAddInst : public IRBinaryInstruction
    {
    public:
        void Apply(IRTranslator *interface) override;

        FAddInst(Value *return_value, Value *lhs, Value *rhs);
    };
} // namespace city

#endif // CITY_FADDINST_H
