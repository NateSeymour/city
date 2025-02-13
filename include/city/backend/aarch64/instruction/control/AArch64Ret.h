#ifndef AARCH64RET_H
#define AARCH64RET_H

#include "city/backend/aarch64/instruction/AArch64Instruction.h"

namespace city
{
    class AArch64Ret : public AArch64Instruction
    {
    public:
        static AArch64Ret Z()
        {
            union
            {
                struct
                {
                    unsigned _0 : 5 = 0;
                    unsigned rn : 5 = 0;
                    unsigned _1 : 22 = 0b1101'0110'0101'1111'0000'00;
                };
                std::uint32_t raw;
            } encoding{
                    .rn = 30,
            };

            return {encoding.raw};
        }

        AArch64Ret(std::uint32_t encoding) : AArch64Instruction(encoding) {}
    };
} // namespace city

#endif // AARCH64RET_H
