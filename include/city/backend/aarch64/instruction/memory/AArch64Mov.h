#ifndef AARCH64MOV_H
#define AARCH64MOV_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"

namespace city
{
    class AArch64Mov : public AArch64Instruction
    {
    public:
        [[nodiscard]] static AArch64Mov IS(Register &dst, std::uint16_t imm, std::uint8_t shift16)
        {
            union
            {
                struct
                {
                    unsigned dst : 5 = 0;
                    unsigned imm : 16 = 0;
                    unsigned shift : 2 = 0;
                    unsigned op : 6 = 0b100101;
                    unsigned opc : 2 = 0b10;
                    unsigned sf : 1 = 1;
                };
                std::uint32_t raw;
            } encoding{
                    .dst = dst.GetCode(),
                    .imm = imm,
                    .shift = shift16,
            };

            return {encoding.raw};
        }

        [[nodiscard]] static AArch64Mov KIS(Register &dst, std::uint16_t imm, std::uint8_t shift16)
        {
            union
            {
                struct
                {
                    unsigned dst : 5 = 0;
                    unsigned imm : 16 = 0;
                    unsigned shift : 2 = 0;
                    unsigned op : 6 = 0b100101;
                    unsigned opc : 2 = 0b11;
                    unsigned sf : 1 = 1;
                };
                std::uint32_t raw;
            } encoding{
                    .dst = dst.GetCode(),
                    .imm = imm,
                    .shift = shift16,
            };

            return {encoding.raw};
        }

        [[nodiscard]] static AArch64Mov RS(Register &dst, Register &src)
        {
            union
            {
                struct
                {
                    unsigned dst : 5 = 0;
                    unsigned src2 : 5 = 0b11111;
                    unsigned imm : 6 = 0;
                    unsigned src1 : 5 = 0;
                    unsigned n : 1 = 0;
                    unsigned shift : 2 = 0;
                    unsigned op : 5 = 0b01010;
                    unsigned opc : 2 = 0b01;
                    unsigned sf : 1 = 1;
                };
                std::uint32_t raw;
            } encoding{
                    .dst = dst.GetCode(),
                    .src1 = src.GetCode(),
            };

            return {encoding.raw};
        }

        [[nodiscard]] static AArch64Mov FR(Register &dst, Register &src)
        {
            union
            {
                struct
                {
                    unsigned dst : 5 = 0;
                    unsigned src : 5 = 0;
                    unsigned _ : 6 = 0;
                    unsigned opcode : 3 = 0;
                    unsigned rmode : 2 = 0;
                    unsigned n : 1 = 1;
                    unsigned ftype : 2 = 0b00;
                    unsigned op : 7 = 0b0011110;
                    unsigned sf : 1 = 1;
                };
                std::uint32_t raw;
            } encoding{
                    .dst = dst.GetCode(),
                    .src = src.GetCode(),
            };

            if (dst.GetValueType() == RegisterType::FloatingPoint && src.GetValueType() == RegisterType::Integer)
            {
                encoding.ftype = 0b01;
                encoding.rmode = 0b00;
                encoding.opcode = 0b111;
            }
            else if (dst.GetValueType() == RegisterType::Integer && src.GetValueType() == RegisterType::FloatingPoint)
            {
                encoding.ftype = 0b01;
                encoding.rmode = 0b00;
                encoding.opcode = 0b110;
            }

            return {encoding.raw};
        }

        AArch64Mov(std::uint32_t encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64MOV_H
