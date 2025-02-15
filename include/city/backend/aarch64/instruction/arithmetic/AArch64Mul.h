#ifndef AARCH64MUL_H
#define AARCH64MUL_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"

namespace city
{
    class AArch64Mul : public AArch64Instruction
    {
    public:
        [[nodiscard]] static AArch64Mul R(Register &dst, Register &src1, Register &src2)
        {
            union
            {
                struct
                {
                    unsigned dst : 5 = 0;
                    unsigned src1 : 5 = 0;
                    unsigned _ : 6 = 0b0111'11;
                    unsigned src2 : 5 = 0;
                    unsigned op : 10 = 0b0011'0110'00;
                    unsigned sf : 1 = 1;
                };
                std::uint32_t raw;
            } encoding{
                    .dst = dst.GetCode(),
                    .src1 = src1.GetCode(),
                    .src2 = src2.GetCode(),
            };

            return {encoding.raw};
        }

        [[nodiscard]] static AArch64Mul F(Register &dst, Register &src1, Register &src2)
        {
            union
            {
                struct
                {
                    unsigned dst : 5 = 0;
                    unsigned src1 : 5 = 0;
                    unsigned _ : 6 = 0b0000'10;
                    unsigned src2 : 5 = 0;
                    unsigned n : 1 = 1;
                    unsigned ftype : 2 = 0b01;
                    unsigned op : 8 = 0b00011110;
                };
                std::uint32_t raw;
            } encoding{
                    .dst = dst.GetCode(),
                    .src1 = src1.GetCode(),
                    .src2 = src2.GetCode(),
            };

            return {encoding.raw};
        }

        AArch64Mul(std::uint32_t encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64MUL_H
