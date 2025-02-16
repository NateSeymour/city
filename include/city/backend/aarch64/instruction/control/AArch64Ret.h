#ifndef AARCH64RET_H
#define AARCH64RET_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"

namespace city
{
    class AArch64Ret : public AArch64Instruction
    {
    public:
        [[nodiscard]] static AArch64Ret Z()
        {
            return AArch64Encoding{
                    .ubr{
                            .op4 = 0b0000'0,
                            .rn = 30,
                            .op3 = 0b0000'00,
                            .op2 = 0b1111'1,
                            .opc = 0b0010,
                    },
            };
        }

        AArch64Ret(AArch64Encoding encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64RET_H
