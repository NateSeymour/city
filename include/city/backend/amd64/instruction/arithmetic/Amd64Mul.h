#ifndef CITY_AMD64MUL_H
#define CITY_AMD64MUL_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Mul : public Amd64Instruction
    {
    public:
        static Amd64Mul RM32(Register &dst, Register &src, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            Amd64Mul inst{};

            inst.SetOpcode({0x0F, 0xAF});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }

        static Amd64Mul RM64(Register &dst, Register &src, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            Amd64Mul inst{};

            inst.SetREX(&src, &dst);
            inst.SetOpcode({0x0F, 0xAF});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }

        static Amd64Mul RMX(Register &dst, Register &src, std::size_t size, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            if (size <= 4)
            {
                return Amd64Mul::RM32(dst, src, mod, disp);
            }

            if (size <= 8)
            {
                return Amd64Mul::RM64(dst, src, mod, disp);
            }

            throw std::runtime_error("operands too large");
        }

        static Amd64Mul SDA(Register &dst, Register &src, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0)
        {
            Amd64Mul inst{};

            inst.SetOpcode({0xF2, 0x0F, 0x59});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }
    };
} // namespace city

#endif // CITY_AMD64MUL_H
