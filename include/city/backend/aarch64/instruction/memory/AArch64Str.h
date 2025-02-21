#ifndef AARCH64STR_H
#define AARCH64STR_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"

namespace city
{
    class AArch64Str : public AArch64Instruction
    {
    public:
        [[nodiscard]] static AArch64Str I(Register &dst, Register &src1, std::uint16_t src2 = 0, std::size_t size = 8)
        {
            // Quick integer log2 calculation with no floating point rounding
            // https://stackoverflow.com/a/994623/11793055
            unsigned opsize = 0;
            while (size >>= 1)
            {
                opsize++;
            }

            return {AArch64Encoding{
                    .lsrui{
                            .rt = dst.GetCode(),
                            .rm = src1.GetCode(),
                            .imm = src2,
                            .opc = 0b00,
                            .v = 0b0,
                            .size = opsize,
                    },
            }};
        }

        [[nodiscard]] static AArch64Str P(Register &dst, std::int16_t src1, Register &src2, Register &src3, std::size_t size = 8)
        {
            unsigned opc = (size / 8) << 1;
            return {AArch64Encoding{
                    .lsrpo{
                            .rt = src2.GetCode(),
                            .rn = dst.GetCode(),
                            .rt2 = src3.GetCode(),
                            .imm = static_cast<unsigned>(src1 / 8),
                            .l = 0,
                            .v = 0b0,
                            .opc = opc,
                    },
            }};
        }

        [[nodiscard]] static AArch64Str F(Register &dst, Register &src1, std::uint16_t src2 = 0, std::size_t size = 8)
        {
            // Quick integer log2 calculation with no floating point rounding
            // https://stackoverflow.com/a/994623/11793055
            unsigned opsize = 0;
            while (size >>= 1)
            {
                opsize++;
            }

            return {AArch64Encoding{
                    .lsrui{
                            .rt = dst.GetCode(),
                            .rm = src1.GetCode(),
                            .imm = src2,
                            .opc = 0b00,
                            .v = 0b1,
                            .size = opsize,
                    },
            }};
        }

        AArch64Str(AArch64Encoding encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64STR_H
