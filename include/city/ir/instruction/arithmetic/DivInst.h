#ifndef CITY_DIVINST_H
#define CITY_DIVINST_H

#include <city/ir/instruction/IRBinaryInstruction.h>

namespace city
{
    class DivInst : public IRBinaryInstruction
    {
    public:
        void Apply(IRTranslator *interface) override;

        DivInst(Type type, Value *lhs, Value *rhs);
    };
} // namespace city

#endif // CITY_DIVINST_H
