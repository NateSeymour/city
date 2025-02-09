#ifndef CITY_AMD64DIV_H
#define CITY_AMD64DIV_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Div : public Amd64Instruction
    {
    public:
        static Amd64Div M32(Amd64Register &src, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            Amd64Div inst;

            inst.SetOpcode({0xF7});
            inst.SetModRM(6, src.GetCode(), mod, disp);

            return inst;
        }

        static Amd64Div M64(Amd64Register &src, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            Amd64Div inst;

            inst.SetREX(nullptr, &src);
            inst.SetOpcode({0xF7});
            inst.SetModRM(6, src.GetCode(), mod, disp);

            return inst;
        }

        static Amd64Div MX(Amd64Register &src, std::size_t size, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            if (size <= 4)
            {
                return Amd64Div::M32(src, mod, disp);
            }

            if (size <= 8)
            {
                return Amd64Div::M64(src, mod, disp);
            }

            throw std::runtime_error("operands too large");
        }

        static Amd64Div SDA(Amd64Register &dst, Amd64Register &src, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            Amd64Div inst{};

            inst.SetOpcode({0xF2, 0x0F, 0x5E});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }
    };
} // namespace city

#endif // CITY_AMD64DIV_H
