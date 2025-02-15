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
            return {AArch64Encoding{
                    .dp_add_sub_i{
                            .sf = sf,
                            .op = 0b0,
                            .s = 0b0,
                            .sh = 0b0,
                            .imm = src2,
                            .rn = src1.GetCode(),
                            .rd = dst.GetCode(),
                    },
            }};
        }

        [[nodiscard]] static AArch64Add R(Register &dst, Register &src1, Register &src2, std::size_t size = 8)
        {
            unsigned sf = size / 8;
            return {AArch64Encoding{
                    .dp_add_sub_shift{
                            .sf = sf,
                            .op = 0b0,
                            .s = 0b0,
                            .shift = 0b0,
                            .rm = src1.GetCode(),
                            .imm = 0b0,
                            .rn = src2.GetCode(),
                            .rd = dst.GetCode(),
                    },
            }};
        }

        [[nodiscard]] static AArch64Add F(Register &dst, Register &src1, Register &src2, std::size_t size = 8)
        {
            unsigned ptype = (size / 4) - 1;
            return {AArch64Encoding{
                    .fdp2{
                            .m = 0b0,
                            .s = 0b0,
                            .ptype = ptype,
                            .rm = src1.GetCode(),
                            .opcode = 0b0010,
                            .rn = src2.GetCode(),
                            .rd = dst.GetCode(),
                    },
            }};
        }

        AArch64Add(std::uint32_t encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64ADD_H
