#ifndef AMD64SUB_H
#define AMD64SUB_H

#include "backend/amd64/instruction/Amd64Instruction.h"

namespace city
{
    class Amd64Sub : public Amd64Instruction
    {
    public:
        static constexpr Amd64Sub MR64(Amd64RegisterCode dst, Amd64RegisterCode src)
        {
            Amd64Sub inst;

            auto rexw = static_cast<std::uint8_t>(Amd64PrefixCode::REXW);
            inst.SetPrefix({rexw});
            inst.SetOpcode({0x29});
            inst.SetModRM(src, dst, Amd64Mod::Register);

            return inst;
        }
    };
} // namespace city

#endif // AMD64SUB_H
