#ifndef CITY_AMD64MUL_H
#define CITY_AMD64MUL_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Mul : public Amd64Instruction
    {
    public:
        /// (I)MUL r/m64
        [[nodiscard]] static Amd64Mul M(Register &src, bool is_signed = false, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            std::uint8_t reg = is_signed ? 5 : 4;
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

        /// IMUL r64, r/m64
        [[nodiscard]] static Amd64Mul RM(Register &dst, Register &src, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            return {Amd64Encoding{
                    .rex{{
                            .w = true,
                            .r = dst.IsExtension(),
                            .b = src.IsExtension(),
                    }},
                    .opcode = {0x0F, 0xAF},
                    .mod{{
                            .access = access,
                            .reg_code = dst.GetCode(),
                            .rm_code = src.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        /// MUL(SS|SD) xmm1, xmm2/m(32|64)
        [[nodiscard]] static Amd64Mul FA(Register &dst, Register &src, std::size_t precision = 8, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            std::uint8_t opcode_leader = precision == 8 ? 0xF2 : 0xF3;
            return {Amd64Encoding{
                    .rex{{
                            .r = dst.IsExtension(),
                            .b = src.IsExtension(),
                    }},
                    .opcode = {opcode_leader, 0x0F, 0x59},
                    .mod{{
                            .access = access,
                            .reg_code = dst.GetCode(),
                            .rm_code = src.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        Amd64Mul(Amd64Encoding encoding) : Amd64Instruction(encoding) {}
    };
} // namespace city

#endif // CITY_AMD64MUL_H
