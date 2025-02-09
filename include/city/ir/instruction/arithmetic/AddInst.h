#ifndef CITY_ADDINST_H
#define CITY_ADDINST_H

#include <city/ir/instruction/IRBinaryInstruction.h>

namespace city
{
    class AddInst : public IRBinaryInstruction
    {
    public:
        void Apply(IRTranslator *interface) override;

        AddInst(Type type, Value *lhs, Value *rhs);
    };
} // namespace city

#endif // CITY_ADDINST_H
