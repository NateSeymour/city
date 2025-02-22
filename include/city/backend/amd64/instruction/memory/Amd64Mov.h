#ifndef CITY_AMD64MOVMR64_H
#define CITY_AMD64MOVMR64_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>
#include <stdexcept>

namespace city
{
    class Amd64Mov : public Amd64Instruction
    {
    public:
        static Amd64Mov OI32(Register &dst, std::uint32_t data) noexcept
        {
            Amd64Mov inst;

            auto buffer = reinterpret_cast<std::uint8_t *>(&data);

            std::uint8_t opcode = 0xB8 + dst.GetCode();
            inst.SetOpcode({opcode});
            inst.SetImmediate({buffer[0], buffer[1], buffer[2], buffer[3]});

            return inst;
        }

        static Amd64Mov OI64(Register &dst, std::uint64_t data) noexcept
        {
            Amd64Mov inst;

            auto buffer = reinterpret_cast<std::uint8_t *>(&data);

            inst.SetREX(nullptr, &dst);
            std::uint8_t opcode = 0xB8 + dst.GetCode();
            inst.SetOpcode({opcode});
            inst.SetImmediate({
                    buffer[0],
                    buffer[1],
                    buffer[2],
                    buffer[3],
                    buffer[4],
                    buffer[5],
                    buffer[6],
                    buffer[7],
            });

            return inst;
        }

        static Amd64Mov OIX(Register &dst, std::vector<std::uint8_t> const &buffer)
        {
            if (buffer.size() <= 4)
            {
                std::uint32_t data = *reinterpret_cast<std::uint32_t const *>(buffer.data());
                return Amd64Mov::OI32(dst, data);
            }

            if (buffer.size() <= 8)
            {
                std::uint64_t data = *reinterpret_cast<std::uint64_t const *>(buffer.data());
                return Amd64Mov::OI64(dst, data);
            }

            throw std::runtime_error("data buffer is too big to fit into immediate value");
        }

        static Amd64Mov MR32(Register &dst, Register &src, Amd64Access mod = Amd64Access::Value, std::int32_t disp = 0) noexcept
        {
            Amd64Mov inst{};

            inst.SetOpcode({0x89});
            inst.SetModRM(src.GetCode(), dst.GetCode(), mod, disp);

            return inst;
        }

        static Amd64Mov MR64(Register &dst, Register &src, Amd64Access mod = Amd64Access::Value, std::int32_t disp = 0) noexcept
        {
            Amd64Mov inst{};

            inst.SetREX(&src, &dst);
            inst.SetOpcode({0x89});
            inst.SetModRM(src.GetCode(), dst.GetCode(), mod, disp);

            return inst;
        }

        static Amd64Mov MRX(Register &dst, Register &src, std::size_t size, Amd64Access mod = Amd64Access::Value, std::int32_t disp = 0)
        {
            if (size <= 4)
            {
                return Amd64Mov::MR32(dst, src, mod, disp);
            }

            if (size <= 8)
            {
                return Amd64Mov::MR64(dst, src, mod, disp);
            }

            throw std::runtime_error("data is too big to fit into container");
        }

        static Amd64Mov RM32(Register &dst, Register &src, Amd64Access mod = Amd64Access::Value, std::int32_t disp = 0) noexcept
        {
            Amd64Mov inst{};

            inst.SetOpcode({0x8B});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }

        static Amd64Mov RM64(Register &dst, Register &src, Amd64Access mod = Amd64Access::Value, std::int32_t disp = 0) noexcept
        {
            Amd64Mov inst{};

            inst.SetREX(&src, &dst);
            inst.SetOpcode({0x8B});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }

        static Amd64Mov RMX(Register &dst, Register &src, std::size_t size, Amd64Access mod = Amd64Access::Value, std::int32_t disp = 0)
        {
            if (size <= 4)
            {
                return Amd64Mov::RM32(dst, src, mod, disp);
            }

            if (size <= 8)
            {
                return Amd64Mov::RM64(dst, src, mod, disp);
            }

            throw std::runtime_error("data is too big to fit into single register");
        }

        static Amd64Mov SDA(Register &dst, Register &src, Amd64Access mod = Amd64Access::Value, std::int32_t disp = 0)
        {
            Amd64Mov inst{};

            inst.SetOpcode({0xF2, 0x0F, 0x10});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }
    };
} // namespace city

#endif // CITY_AMD64MOVMR64_H
