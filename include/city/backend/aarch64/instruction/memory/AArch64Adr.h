#ifndef AARCH64ADR_H
#define AARCH64ADR_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"

namespace city
{
    class AArch64Adr : public AArch64Instruction
    {
    public:
        AArch64Adr(AArch64Encoding encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64ADR_H
