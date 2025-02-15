#ifndef AARCH64ADD_H
#define AARCH64ADD_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"

namespace city
{
    class AArch64Add : public AArch64Instruction
    {
    public:
        static AArch64Add I(Register &dst, Register &src1, std::uint16_t src2)
        {
            union
            {
                struct
                {
                    unsigned dst : 5 = 0;
                    unsigned src : 5 = 0;
                    unsigned imm : 12 = 0;
                    unsigned sh : 1 = 0;
                    unsigned op : 6 = 0b100010;
                    unsigned s : 1 = 1;
                    unsigned op1 : 1 = 0;
                    unsigned sf : 1 = 1;
                };
                std::uint32_t raw;
            } encoding{
                    .dst = dst.GetCode(),
                    .src = src1.GetCode(),
                    .imm = src2,
            };

            return {encoding.raw};
        }

        static AArch64Add R(Register &dst, Register &src1, Register &src2)
        {
            union
            {
                struct
                {
                    unsigned dst : 5 = 0;
                    unsigned src1 : 5 = 0;
                    unsigned imm : 6 = 0;
                    unsigned src2 : 5 = 0;
                    unsigned n : 1 = 0;
                    unsigned shift : 2 = 0;
                    unsigned op : 5 = 0b01011;
                    unsigned s : 1 = 0;
                    unsigned op1 : 1 = 0;
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

        static AArch64Add F(Register &dst, Register &src1, Register &src2)
        {
            union
            {
                struct
                {
                    unsigned dst : 5 = 0;
                    unsigned src1 : 5 = 0;
                    unsigned _ : 6 = 0b001010;
                    unsigned src2 : 5 = 0;
                    unsigned n : 1 = 1;
                    unsigned ftype : 2 = 0b01;
                    unsigned op : 8 = 0b0001'1110;
                };
                std::uint32_t raw;
            } encoding{
                    .dst = dst.GetCode(),
                    .src1 = src1.GetCode(),
                    .src2 = src2.GetCode(),
            };

            return {encoding.raw};
        }

        AArch64Add(std::uint32_t encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64ADD_H
