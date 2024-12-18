#ifndef CITY_AMD64MOVMR64_H
#define CITY_AMD64MOVMR64_H

#include "backend/x86/instruction/x86Instruction.h"

namespace city
{
    class Amd64MovMR64 : public x86Instruction
    {
    public:
        Amd64MovMR64(x86RegisterCode dst, x86RegisterCode src)
        {
            auto rexw = static_cast<std::uint8_t>(Amd64PrefixCode::REXW);
            this->SetPrefix({rexw});
            this->SetOpcode({0x89});
            this->SetModRM(src, dst, x86Mod::Register);
        }
    };
} // namespace city

#endif // CITY_AMD64MOVMR64_H
