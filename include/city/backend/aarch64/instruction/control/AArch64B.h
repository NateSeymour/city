#ifndef AARCH64B_H
#define AARCH64B_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"

namespace city
{
    class AArch64B : public AArch64Instruction
    {
    public:
        [[nodiscard]] static AArch64B R(Register &src1, bool link = false)
        {
            unsigned opc = link ? 0b0001 : 0b0000;
            return {AArch64Encoding{
                    .ubr{
                            .op4 = 0b0000'0,
                            .rn = src1.GetCode(),
                            .op3 = 0b0000'00,
                            .op2 = 0b1111'1,
                            .opc = opc,
                    },
            }};
        }

        AArch64B(AArch64Encoding encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64B_H
