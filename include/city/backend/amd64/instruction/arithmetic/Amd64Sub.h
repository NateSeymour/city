#ifndef AMD64SUB_H
#define AMD64SUB_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Sub : public Amd64Instruction
    {
    public:
        static Amd64Sub MI64(Amd64RegisterCode dst, std::uint32_t data)
        {
            Amd64Sub inst;

            auto buffer = reinterpret_cast<std::uint8_t *>(&data);

            auto rexw = static_cast<std::uint8_t>(Amd64PrefixCode::REXW);
            inst.SetPrefix({rexw});
            inst.SetOpcode({0x81});
            inst.SetModRM(5, dst, Amd64RegisterAccessType::Value);
            inst.SetImmediate({
                    buffer[0],
                    buffer[1],
                    buffer[2],
                    buffer[3],
            });

            return inst;
        }

        static Amd64Sub MR64(Amd64RegisterCode dst, Amd64RegisterCode src)
        {
            Amd64Sub inst;

            auto rexw = static_cast<std::uint8_t>(Amd64PrefixCode::REXW);
            inst.SetPrefix({rexw});
            inst.SetOpcode({0x29});
            inst.SetModRM(src, dst, Amd64RegisterAccessType::Value);

            return inst;
        }

        static Amd64Sub SDA(Amd64RegisterCode dst, Amd64RegisterCode src, Amd64RegisterAccessType mod = Amd64RegisterAccessType::Value)
        {
            Amd64Sub inst{};

            inst.SetOpcode({0xF2, 0x0F, 0x5C});
            inst.SetModRM(dst, src, mod);

            return inst;
        }
    };
} // namespace city

#endif // AMD64SUB_H
