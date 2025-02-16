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
            return AArch64Encoding{
                    .dp3{
                            .rd = dst.GetCode(),
                            .rn = src1.GetCode(),
                            .ra = 0b1111'1,
                            .op = 0b0,
                            .rm = src2.GetCode(),
                            .op31 = 0b0,
                            .op54 = 0b0,
                            .sf = sf,
                    },
            };
        }

        [[nodiscard]] static AArch64Mul F(Register &dst, Register &src1, Register &src2, std::size_t size = 8)
        {
            unsigned ptype = (size / 4) - 1;
            return AArch64Encoding{
                    .fdp2{
                            .rd = dst.GetCode(),
                            .rn = src1.GetCode(),
                            .opcode = 0b0000,
                            .rm = src2.GetCode(),
                            .ptype = ptype,
                            .s = 0b0,
                            .m = 0b0,
                    },
            };
        }

        AArch64Mul(AArch64Encoding encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64MUL_H
