#ifndef AMD64SUB_H
#define AMD64SUB_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Sub : public Amd64Instruction
    {
    public:
        /// SUB r/m64, imm32
        [[nodiscard]] static Amd64Sub MI(Register &dst, std::uint32_t src, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            return {Amd64Encoding{
                    .rex{{
                            .w = true,
                            .b = dst.IsExtension(),
                    }},
                    .opcode = {0x81},
                    .mod{{
                            .access = access,
                            .reg_code = 5,
                            .rm_code = dst.GetCode(),
                    }},
                    .disp = disp,
                    .imm = src,
            }};
        }

        /// SUB r/m64, r64
        [[nodiscard]] static Amd64Sub MR(Register &dst, Register &src, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            return {Amd64Encoding{
                    .rex{{
                            .w = true,
                            .r = src.IsExtension(),
                            .b = dst.IsExtension(),
                    }},
                    .opcode = {0x29},
                    .mod{{
                            .access = access,
                            .reg_code = src.GetCode(),
                            .rm_code = dst.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        /// SUB r64, r/m64
        [[nodiscard]] static Amd64Sub RM(Register &dst, Register &src, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            return {Amd64Encoding{
                    .rex{{
                            .w = true,
                            .r = dst.IsExtension(),
                            .b = src.IsExtension(),
                    }},
                    .opcode = {0x2B},
                    .mod{{
                            .access = access,
                            .reg_code = dst.GetCode(),
                            .rm_code = src.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        /// SUB(SS|SD) xmm1, xmm2/m(32|64)
        [[nodiscard]] static Amd64Sub AS(Register &dst, Register &src, std::size_t precision = 8, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            std::uint8_t opcode_leader = precision == 8 ? 0xF2 : 0xF3;
            return {Amd64Encoding{
                    .rex{{
                            .r = dst.IsExtension(),
                            .b = src.IsExtension(),
                    }},
                    .opcode = {opcode_leader, 0x0F, 0x5C},
                    .mod{{
                            .access = access,
                            .reg_code = dst.GetCode(),
                            .rm_code = src.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        Amd64Sub(Amd64Encoding encoding) : Amd64Instruction(encoding) {}
    };
} // namespace city

#endif // AMD64SUB_H
