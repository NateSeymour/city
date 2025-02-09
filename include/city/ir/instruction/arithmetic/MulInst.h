#ifndef CITY_MULINST_H
#define CITY_MULINST_H

#include <city/ir/instruction/IRBinaryInstruction.h>

namespace city
{
    class MulInst : public IRBinaryInstruction
    {
    public:
        void Apply(IRTranslator *interface) override;

        MulInst(Type type, Value *lhs, Value *rhs);
    };
} // namespace city

#endif // CITY_MULINST_H
