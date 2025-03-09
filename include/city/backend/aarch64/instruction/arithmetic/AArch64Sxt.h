#ifndef AARCH64SXT_H
#define AARCH64SXT_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"
#include "city/container/Register.h"

namespace city
{
    class AArch64Sxt : public AArch64Instruction
    {
    public:
        /// SXT(B|H|W) <Rd>, <Rn>
        [[nodiscard]] static AArch64Sxt R(Register &dst, Register &src, std::size_t size = 1)
        {
            std::uint8_t imms = 0xFF >> (5 - (size / 2));

            return {AArch64EncDPBI{
                    .rd = dst.GetCode(),
                    .rn = src.GetCode(),
                    .imms = imms,
                    .immr = 0b0,
                    .n = 0b1,
                    .opc = 0b00,
                    .sf = 0b1,
            }};
        }

        AArch64Sxt(AArch64Encoding encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64SXT_H
