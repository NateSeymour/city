#ifndef AMD64SUB_H
#define AMD64SUB_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Sub : public Amd64Instruction
    {
    public:
        static Amd64Sub MI64(Amd64Register &dst, std::uint32_t data, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            Amd64Sub inst;

            auto buffer = reinterpret_cast<std::uint8_t *>(&data);

            inst.SetREX(nullptr, &dst);
            inst.SetOpcode({0x81});
            inst.SetModRM(5, dst.GetCode(), mod, disp);
            inst.SetImmediate({
                    buffer[0],
                    buffer[1],
                    buffer[2],
                    buffer[3],
            });

            return inst;
        }

        static Amd64Sub MR64(Amd64Register &dst, Amd64Register &src, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            Amd64Sub inst;

            inst.SetREX(&src, &dst);
            inst.SetOpcode({0x29});
            inst.SetModRM(src.GetCode(), dst.GetCode(), mod, disp);

            return inst;
        }

        static Amd64Sub SDA(Amd64Register &dst, Amd64Register &src, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            Amd64Sub inst{};

            inst.SetOpcode({0xF2, 0x0F, 0x5C});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }
    };
} // namespace city

#endif // AMD64SUB_H
