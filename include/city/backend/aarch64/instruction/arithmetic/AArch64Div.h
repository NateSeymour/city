#ifndef AARCH64DIV_H
#define AARCH64DIV_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"

namespace city
{
    class AArch64Div : public AArch64Instruction
    {
    public:
        [[nodiscard]] static AArch64Div R(Register &dst, Register &src1, Register &src2, std::size_t size = 8)
        {
            unsigned sf = size / 8;
            return {AArch64EncDP2{
                    .rd = dst.GetCode(),
                    .rn = src1.GetCode(),
                    .opcode = 0b0000'11,
                    .rm = src2.GetCode(),
                    .s = 0b0,
                    .sf = sf,
            }};
        }

        [[nodiscard]] static AArch64Div F(Register &dst, Register &src1, Register &src2, std::size_t size = 8)
        {
            unsigned ptype = (size / 4) - 1;
            return {AArch64EncFDP2{
                    .rd = dst.GetCode(),
                    .rn = src1.GetCode(),
                    .opcode = 0b0001,
                    .rm = src2.GetCode(),
                    .ptype = ptype,
                    .s = 0b0,
                    .m = 0b0,
            }};
        }

        AArch64Div(AArch64Encoding encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64DIV_H
