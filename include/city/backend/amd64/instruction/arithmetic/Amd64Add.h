#ifndef AMD64ADD_H
#define AMD64ADD_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Add : public Amd64Instruction
    {
    public:
        static Amd64Add MR64(Amd64RegisterCode dst, Amd64RegisterCode src)
        {
            Amd64Add inst{};

            auto rexw = static_cast<std::uint8_t>(Amd64PrefixCode::REXW);
            inst.SetPrefix({rexw});
            inst.SetOpcode({0x01});
            inst.SetModRM(src, dst, Amd64RegisterAccessType::Value);

            return inst;
        }

        static Amd64Add SDA(Amd64RegisterCode dst, Amd64RegisterCode src, Amd64RegisterAccessType mod = Amd64RegisterAccessType::Value)
        {
            Amd64Add inst{};

            inst.SetOpcode({0xF2, 0x0F, 0x58});
            inst.SetModRM(dst, src, mod);

            return inst;
        }
    };
} // namespace city

#endif // AMD64ADD_H
