#ifndef CITY_AMD64DIV_H
#define CITY_AMD64DIV_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Div : public Amd64Instruction
    {
    public:
        /// (I)DIV r/m64
        [[nodiscard]] static Amd64Div M(Register &src, bool is_signed = false, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            std::uint8_t reg = is_signed ? 7 : 6;
            return {Amd64Encoding{
                    .rex{{
                            .w = true,
                            .b = src.IsExtension(),
                    }},
                    .opcode = {0xF7},
                    .mod{{
                            .access = access,
                            .reg_code = reg,
                            .rm_code = src.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        /// DIV(SS|SD) xmm1, xmm2/m(32|64)
        [[nodiscard]] static Amd64Div AS(Register &dst, Register &src, std::size_t precision = 8, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            std::uint8_t opcode_leader = precision == 8 ? 0xF2 : 0xF3;
            return {Amd64Encoding{
                    .rex{{
                            .r = dst.IsExtension(),
                            .b = src.IsExtension(),
                    }},
                    .opcode = {opcode_leader, 0x0F, 0x5E},
                    .mod{{
                            .access = access,
                            .reg_code = dst.GetCode(),
                            .rm_code = src.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        Amd64Div(Amd64Encoding encoding) : Amd64Instruction(encoding) {}
    };
} // namespace city

#endif // CITY_AMD64DIV_H
