#ifndef CITY_AMD64POPO64_H
#define CITY_AMD64POPO64_H

#include "city/backend/amd64/instruction/Amd64Instruction.h"

namespace city
{
    class Amd64Pop : public Amd64Instruction
    {
    public:
        /// POP r64
        [[nodiscard]] static Amd64Pop O(Register &dst)
        {
            std::uint8_t opcode = 0x58 + dst.GetCode()();
            return {Amd64Encoding{
                    .rex{{
                            .r = dst.IsExtension(),
                    }},
                    .opcode = {opcode},
            }};
        }

        Amd64Pop(Amd64Encoding encoding) : Amd64Instruction(encoding) {}
    };
} // namespace city

#endif // CITY_AMD64POPO64_H
