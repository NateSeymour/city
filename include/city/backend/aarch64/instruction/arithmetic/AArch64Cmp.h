#ifndef AARCH64CMP_H
#define AARCH64CMP_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"
#include "city/container/Register.h"

namespace city
{
    class AArch64Cmp : public AArch64Instruction
    {
    public:
        [[nodiscard]] static AArch64Cmp R(Register &src1, Register &src2, std::size_t size = 8)
        {
            unsigned sf = size / 8;
            return {AArch64DPASS{
                    .rd = 31,
                    .rn = src1.GetCode(),
                    .imm = 0b0,
                    .rm = src2.GetCode(),
                    .shift = 0b0,
                    .s = 0b1,
                    .op = 0b1,
                    .sf = sf,
            }};
        }

        AArch64Cmp(AArch64Encoding encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64CMP_H
