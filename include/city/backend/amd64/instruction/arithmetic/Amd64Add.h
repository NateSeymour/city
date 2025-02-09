#ifndef AMD64ADD_H
#define AMD64ADD_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Add : public Amd64Instruction
    {
    public:
        static Amd64Add RM32(Amd64Register &dst, Amd64Register &src, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            Amd64Add inst{};

            inst.SetOpcode({0x03});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }

        static Amd64Add RM64(Amd64Register &dst, Amd64Register &src, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            Amd64Add inst{};

            inst.SetREX(&src, &dst);
            inst.SetOpcode({0x03});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }

        static Amd64Add RMX(Amd64Register &dst, Amd64Register &src, std::size_t size, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            if (size <= 4)
            {
                return Amd64Add::RM32(dst, src, mod, disp);
            }

            if (size <= 8)
            {
                return Amd64Add::RM64(dst, src, mod, disp);
            }

            throw std::runtime_error("operands too large");
        }

        static Amd64Add SDA(Amd64Register &dst, Amd64Register &src, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            Amd64Add inst{};

            inst.SetOpcode({0xF2, 0x0F, 0x58});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }
    };
} // namespace city

#endif // AMD64ADD_H
