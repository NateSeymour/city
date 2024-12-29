#ifndef CITY_AMD64PUSHO64_H
#define CITY_AMD64PUSHO64_H

#include "backend/amd64/instruction/Amd64Instruction.h"

namespace city
{
    class Amd64PushO64 : public Amd64Instruction
    {
    public:
        Amd64PushO64(Amd64RegisterCode reg)
        {
            std::uint8_t opcode = 0x50 + static_cast<std::uint8_t>(reg);
            this->SetOpcode({opcode});
        }
    };
} // namespace city

#endif // CITY_AMD64PUSHO64_H
