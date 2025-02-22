#ifndef CITY_AMD64MOVMR64_H
#define CITY_AMD64MOVMR64_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>
#include <stdexcept>

namespace city
{
    class Amd64Mov : public Amd64Instruction
    {
    public:
        /// MOV r/m(8|16|32|64), r(8|16|32|64)
        [[nodiscard]] static Amd64Mov MR(Register &dst, Register &src, std::size_t size = 8, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            std::uint8_t opcode = size > 1 ? 0x89 : 0x88;
            return {Amd64Encoding{
                    .rex{{
                            .w = size == 8,
                            .r = src.IsExtension(),
                            .b = dst.IsExtension(),
                    }},
                    .opcode = {opcode},
                    .mod{{
                            .access = access,
                            .reg_code = src.GetCode(),
                            .rm_code = dst.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        /// MOV r(8|16|32|64), r/m(8|16|32|64)
        [[nodiscard]] static Amd64Mov RM(Register &dst, Register &src, std::size_t size = 8, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            std::uint8_t opcode = size > 1 ? 0x8B : 0x8A;
            return {Amd64Encoding{
                    .rex{{
                            .w = size == 8,
                            .r = dst.IsExtension(),
                            .b = src.IsExtension(),
                    }},
                    .opcode = {opcode},
                    .mod{{
                            .access = access,
                            .reg_code = dst.GetCode(),
                            .rm_code = src.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        /// MOV r64, imm64
        [[nodiscard]] static Amd64Mov OI(Register &dst, std::uint64_t src)
        {
            std::uint8_t opcode = 0xB8 + dst.GetCode();
            return {Amd64Encoding{
                    .rex{{
                            .w = true,
                            .r = dst.IsExtension(),
                    }},
                    .opcode = {opcode},
                    .imm = src,
            }};
        }

        Amd64Mov(Amd64Encoding encoding) : Amd64Instruction(encoding) {}
    };
} // namespace city

#endif // CITY_AMD64MOVMR64_H
