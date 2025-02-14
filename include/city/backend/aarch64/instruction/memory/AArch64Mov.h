#ifndef AARCH64MOV_H
#define AARCH64MOV_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"

namespace city
{
    class AArch64Mov : public AArch64Instruction
    {
    public:
        [[nodiscard]] static AArch64Mov RS(Register &dst, Register &src1, Register &src2, std::uint8_t shift)
        {
            union
            {
                struct
                {
                    unsigned dst : 5 = 0;
                    unsigned src2 : 5 = 0;
                    unsigned imm : 6 = 0;
                    unsigned src1 : 5 = 0;
                    unsigned n : 1 = 0;
                    unsigned shift : 2 = 0;
                    unsigned op : 5 = 0b01010;
                    unsigned opc : 2 = 0b10;
                    unsigned sf : 1 = 1;
                };
                std::uint32_t raw;
            } encoding{
                    .dst = dst.GetCode(),
                    .src1 = src1.GetCode(),
                    .src2 = src2.GetCode(),
                    .imm = shift,
            };

            return {encoding.raw};
        }

        AArch64Mov(std::uint32_t encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64MOV_H
