#ifndef AARCH64LDR_H
#define AARCH64LDR_H

#include <cmath>
#include "city/backend/aarch64/instruction/AArch64Instruction.h"
#include "city/container/Register.h"

namespace city
{
    class AArch64Ldr : public AArch64Instruction
    {
    public:
        [[nodiscard]] static AArch64Ldr I(Register &dst, Register &src1, std::uint16_t src2 = 0, std::size_t size = 8)
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
                            .opc = 0b01,
                            .v = 0b0,
                            .size = opsize,
                    },
            }};
        }

        [[nodiscard]] static AArch64Ldr F(Register &dst, Register &src1, std::uint16_t src2 = 0, std::size_t size = 8)
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
                            .opc = 0b01,
                            .v = 0b1,
                            .size = opsize,
                    },
            }};
        }

        AArch64Ldr(AArch64Encoding encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64LDR_H
