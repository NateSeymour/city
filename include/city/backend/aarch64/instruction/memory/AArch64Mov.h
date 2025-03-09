#ifndef AARCH64MOV_H
#define AARCH64MOV_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"

namespace city
{
    class AArch64Mov : public AArch64Instruction
    {
    public:
        [[nodiscard]] static AArch64Mov I(Register &dst, std::uint16_t imm = 0, std::uint8_t shift16 = 0, bool erase = true)
        {
            unsigned opc = erase ? 0b10 : 0b11;
            return {AArch64EncDPMI{
                    .rd = dst.GetCode(),
                    .imm = imm,
                    .hw = shift16,
                    .opc = opc,
            }};
        }

        [[nodiscard]] static AArch64Mov R(Register &dst, Register &src)
        {
            return {AArch64EncDPL{
                    .rd = dst.GetCode(),
                    .rn = 31,
                    .imm = 0b0,
                    .rm = src.GetCode(),
                    .n = 0b0,
                    .shift = 0b0,
                    .opc = 0b01,
            }};
        }

        [[nodiscard]] static AArch64Mov FR(Register &dst, Register &src, std::size_t size = 8)
        {
            unsigned sf = size / 8;
            unsigned ptype = (size / 4) - 1;
            unsigned opcode = dst.GetValueType() == RegisterType::FloatingPoint ? 0b111 : 0b110;
            return {AArch64EncFCONV{
                    .rd = dst.GetCode(),
                    .rn = src.GetCode(),
                    .opcode = opcode,
                    .rmode = 0b00,
                    .ptype = ptype,
                    .s = 0b0,
                    .sf = sf,
            }};
        }

        AArch64Mov(AArch64Encoding encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64MOV_H
