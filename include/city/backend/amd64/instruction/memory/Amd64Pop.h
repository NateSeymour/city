#ifndef CITY_AMD64POPO64_H
#define CITY_AMD64POPO64_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Pop : public Amd64Instruction
    {
    public:
        static constexpr Amd64Pop O64(Amd64RegisterCode reg) noexcept
        {
            Amd64Pop inst;

            std::uint8_t opcode = 0x58 + static_cast<std::uint8_t>(reg);
            inst.SetOpcode({opcode});

            return inst;
        }
    };
} // namespace city

#endif // CITY_AMD64POPO64_H
