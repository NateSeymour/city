#ifndef CITY_AMD64MOVMR64_H
#define CITY_AMD64MOVMR64_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Mov : public Amd64Instruction
    {
    public:
        static Amd64Mov OI16(Amd64RegisterCode dst, std::uint16_t data) noexcept
        {
            Amd64Mov inst;

            auto buffer = reinterpret_cast<std::uint8_t *>(&data);

            std::uint8_t opcode = 0xB8 + static_cast<uint8_t>(dst);
            inst.SetOpcode({opcode});
            inst.SetImmediate({buffer[0], buffer[1]});

            return inst;
        }

        static Amd64Mov OI32(Amd64RegisterCode dst, std::uint32_t data) noexcept
        {
            Amd64Mov inst;

            auto buffer = reinterpret_cast<std::uint8_t *>(&data);

            std::uint8_t opcode = 0xB8 + static_cast<uint8_t>(dst);
            inst.SetOpcode({opcode});
            inst.SetImmediate({buffer[0], buffer[1], buffer[2], buffer[3]});

            return inst;
        }

        static Amd64Mov OI64(Amd64RegisterCode dst, std::uint64_t data) noexcept
        {
            Amd64Mov inst;

            auto buffer = reinterpret_cast<std::uint8_t *>(&data);

            auto rexw = static_cast<std::uint8_t>(Amd64PrefixCode::REXW);
            inst.SetPrefix({rexw});

            std::uint8_t opcode = 0xB8 + static_cast<uint8_t>(dst);
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

        static Amd64Mov OIX(Amd64RegisterCode dst, std::vector<std::byte> const &buffer)
        {
            if (buffer.size() <= 2)
            {
                std::uint16_t data = *reinterpret_cast<std::uint16_t const *>(buffer.data());
                return Amd64Mov::OI16(dst, data);
            }

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
