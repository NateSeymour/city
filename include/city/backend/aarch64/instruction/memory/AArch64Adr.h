#ifndef AARCH64ADR_H
#define AARCH64ADR_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"
#include "city/container/Register.h"

namespace city
{
    class AArch64Adr : public AArch64Instruction
    {
    public:
        [[nodiscard]] static AArch64Adr I(Register &dst, std::int32_t src1)
        {
            src1 &= (static_cast<std::uint32_t>(-1) >> 11); // Mask out top 11 bits

            std::int32_t immlo = src1 & 0b11;
            std::int32_t immhi = src1 >> 2;

            return {AArch64EncDPPCR{
                    .rd = dst.GetCode(),
                    .immhi = static_cast<unsigned>(immhi),
                    .immlo = static_cast<unsigned>(immlo),
                    .op = 0b0,
            }};
        }

        AArch64Adr(AArch64Encoding encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64ADR_H
