#ifndef CITY_AMD64MOVMR64_H
#define CITY_AMD64MOVMR64_H

#include "backend/amd64/instruction/Amd64Instruction.h"

namespace city
{
    class Amd64MovMR64 : public Amd64Instruction
    {
    public:
        Amd64MovMR64(Amd64RegisterCode dst, Amd64RegisterCode src)
        {
            auto rexw = static_cast<std::uint8_t>(Amd64PrefixCode::REXW);
            this->SetPrefix({rexw});
            this->SetOpcode({0x89});
            this->SetModRM(src, dst, Amd64Mod::Register);
        }
    };
} // namespace city

#endif // CITY_AMD64MOVMR64_H
