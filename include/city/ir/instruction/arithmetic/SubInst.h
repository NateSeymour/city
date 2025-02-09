#ifndef SUBINST_H
#define SUBINST_H

#include <city/ir/instruction/IRBinaryInstruction.h>

namespace city
{
    class SubInst : public IRBinaryInstruction
    {
    public:
        void Apply(IRTranslator *interface) override;

        SubInst(Type type, Value *lhs, Value *rhs);
    };
} // namespace city

#endif // SUBINST_H
