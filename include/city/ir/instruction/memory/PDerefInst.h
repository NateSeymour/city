#ifndef PDEREFINST_H
#define PDEREFINST_H
#include "city/ir/instruction/IRInstruction.h"

namespace city
{
    class PDerefInst : public IRInstruction
    {
    public:
        PDerefInst(Type type) : IRInstruction(type) {}
    };
} // namespace city

#endif // PDEREFINST_H
