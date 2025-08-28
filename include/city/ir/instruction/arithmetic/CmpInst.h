//
// Created by Nathan Seymour on 8/28/2025.
//

#ifndef CMPINST_H
#define CMPINST_H

#include <city/ir/instruction/IRBinaryInstruction.h>

namespace city
{
    class CmpInst : public IRBinaryInstruction
    {
    public:
        void Apply(IRTranslator *interface) override;

        CmpInst(Type type, Value *lhs, Value *rhs);
    };
} // namespace city

#endif //CMPINST_H
