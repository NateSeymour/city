#ifndef AARCH64MUL_H
#define AARCH64MUL_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"

namespace city
{
    class AArch64Mul : public AArch64Instruction
    {
    public:
        [[nodiscard]] static AArch64Mul R(Register &dst, Register &src1, Register &src2, std::size_t size = 8)
        {
            unsigned sf = size / 8;
            return {AArch64Encoding{
                    .dp3{
                            .sf = sf,
                            .op54 = 0b0,
                            .op31 = 0b0,
                            .rm = src1.GetCode(),
                            .op = 0b0,
                            .ra = 0b1111'1,
                            .rn = src2.GetCode(),
                            .rd = dst.GetCode(),
                    },
            }};
        }

        [[nodiscard]] static AArch64Mul F(Register &dst, Register &src1, Register &src2, std::size_t size = 8)
        {
            unsigned ptype = (size / 4) - 1;
            return {AArch64Encoding{
                    .fdp2{
                            .m = 0b0,
                            .s = 0b0,
                            .ptype = ptype,
                            .rm = src1.GetCode(),
                            .opcode = 0b0000,
                            .rn = src2.GetCode(),
                            .rd = dst.GetCode(),
                    },
            }};
        }

        AArch64Mul(std::uint32_t encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64MUL_H
