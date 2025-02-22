#ifndef AMD64SUB_H
#define AMD64SUB_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Sub : public Amd64Instruction
    {
    public:
        static Amd64Sub MI64(Register &dst, std::uint32_t data, Amd64Access mod = Amd64Access::Value, std::int32_t disp = 0)
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

        static Amd64Sub RM32(Register &dst, Register &src, Amd64Access mod = Amd64Access::Value, std::int32_t disp = 0)
        {
            Amd64Sub inst{};

            inst.SetOpcode({0x2B});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }

        static Amd64Sub RM64(Register &dst, Register &src, Amd64Access mod = Amd64Access::Value, std::int32_t disp = 0)
        {
            Amd64Sub inst{};

            inst.SetREX(&src, &dst);
            inst.SetOpcode({0x2B});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }

        static Amd64Sub RMX(Register &dst, Register &src, std::size_t size, Amd64Access mod = Amd64Access::Value, std::int32_t disp = 0)
        {
            if (size <= 4)
            {
                return Amd64Sub::RM32(dst, src, mod, disp);
            }

            if (size <= 8)
            {
                return Amd64Sub::RM64(dst, src, mod, disp);
            }

            throw std::runtime_error("operands too large");
        }

        static Amd64Sub SDA(Register &dst, Register &src, Amd64Access mod = Amd64Access::Value, std::int32_t disp = 0)
        {
            Amd64Sub inst{};

            inst.SetOpcode({0xF2, 0x0F, 0x5C});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }
    };
} // namespace city

#endif // AMD64SUB_H
