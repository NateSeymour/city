#ifndef CITY_AMD64MOVMR64_H
#define CITY_AMD64MOVMR64_H

#include "backend/amd64/instruction/Amd64Instruction.h"

namespace city
{
    // MR64
    class Amd64Mov : public Amd64Instruction
    {
    public:
        static constexpr Amd64Mov MR64(Amd64RegisterCode dst, Amd64RegisterCode src) noexcept
        {
            Amd64Mov inst{};

            auto rexw = static_cast<std::uint8_t>(Amd64PrefixCode::REXW);
            inst.SetPrefix({rexw});
            inst.SetOpcode({0x89});
            inst.SetModRM(src, dst, Amd64Mod::Register);

            return inst;
        }
    };
} // namespace city

#endif // CITY_AMD64MOVMR64_H
