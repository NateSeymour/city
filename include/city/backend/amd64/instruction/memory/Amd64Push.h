#ifndef CITY_AMD64PUSHO64_H
#define CITY_AMD64PUSHO64_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Push : public Amd64Instruction
    {
    public:
        [[nodiscard]] static Amd64Push O(Register &src) noexcept
        {
            std::uint8_t opcode = 0x50 + src.GetCode();
            return {Amd64Encoding{
                    .opcode = {opcode},
            }};
        }

        Amd64Push(Amd64Encoding encoding) : Amd64Instruction(encoding) {}
    };
} // namespace city

#endif // CITY_AMD64PUSHO64_H
