#ifndef CITY_AMD64POPO64_H
#define CITY_AMD64POPO64_H

#include "backend/amd64/instruction/Amd64Instruction.h"

namespace city
{
    class Amd64PopO64 : public Amd64Instruction
    {
    public:
        Amd64PopO64(Amd64RegisterCode reg)
        {
            std::uint8_t opcode = 0x58 + static_cast<std::uint8_t>(reg);
            this->SetOpcode({opcode});
        }
    };
} // namespace city

#endif // CITY_AMD64POPO64_H
