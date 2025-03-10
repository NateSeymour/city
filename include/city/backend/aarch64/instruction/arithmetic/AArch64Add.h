#ifndef AARCH64ADD_H
#define AARCH64ADD_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"

namespace city
{
    class AArch64Add : public AArch64Instruction
    {
    public:
        [[nodiscard]] static AArch64Add I(Register &dst, Register &src1, std::uint16_t src2, std::size_t size = 8)
        {
            unsigned sf = size / 8;
            return {AArch64EncDPASI{
                    .rd = dst.GetCode(),
                    .rn = src1.GetCode(),
                    .imm = src2,
                    .sh = 0b0,
                    .s = 0b0,
                    .op = 0b0,
                    .sf = sf,
            }};
        }

        [[nodiscard]] static AArch64Add R(Register &dst, Register &src1, Register &src2, std::size_t size = 8)
        {
            unsigned sf = size / 8;
            return {AArch64DPASS{
                    .rd = dst.GetCode(),
                    .rn = src1.GetCode(),
                    .imm = 0b0,
                    .rm = src2.GetCode(),
                    .shift = 0b0,
                    .s = 0b0,
                    .op = 0b0,
                    .sf = sf,
            }};
        }

        [[nodiscard]] static AArch64Add F(Register &dst, Register &src1, Register &src2, std::size_t size = 8)
        {
            unsigned ptype = (size / 4) - 1;
            return {AArch64EncFDP2{
                    .rd = dst.GetCode(),
                    .rn = src1.GetCode(),
                    .opcode = 0b0010,
                    .rm = src2.GetCode(),
                    .ptype = ptype,
                    .s = 0b0,
                    .m = 0b0,
            }};
        }

        AArch64Add(AArch64Encoding encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64ADD_H
