#ifndef CITY_AMD64PUSHO64_H
#define CITY_AMD64PUSHO64_H

#include "backend/amd64/instruction/Amd64Instruction.h"

namespace city
{
    class Amd64Push : public Amd64Instruction
    {
    public:
        static constexpr Amd64Push O64(Amd64RegisterCode reg) noexcept
        {
            Amd64Push inst{};

            std::uint8_t opcode = 0x50 + static_cast<std::uint8_t>(reg);
            inst.SetOpcode({opcode});

            return inst;
        }
    };
} // namespace city

#endif // CITY_AMD64PUSHO64_H
