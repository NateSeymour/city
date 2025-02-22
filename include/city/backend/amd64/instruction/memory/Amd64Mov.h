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

        /**
         * MOVSX(D) r64, r/m(8|16|32|64)
         * Moves value into an r64 register, sign-extending if necessary.
         */
        [[nodiscard]] static Amd64Mov RMSX(Register &dst, Register &src, std::size_t size = 8, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            ByteBuffer<3> opcode;
            if (size <= 1)
            {
                opcode = {0x0F, 0xBE};
            }
            else if (size <= 2)
            {
                opcode = {0x0F, 0xBF};
            }
            else if (size <= 4)
            {
                opcode = {0x63};
            }
            else if (size <= 8)
            {
                opcode = {0x8B}; // Standard MOV
            }

            return {Amd64Encoding{
                    .rex{{
                            .w = true,
                            .r = dst.IsExtension(),
                            .b = src.IsExtension(),
                    }},
                    .opcode = opcode,
                    .mod{{
                            .access = access,
                            .reg_code = dst.GetCode(),
                            .rm_code = src.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        /// MOV r64, imm64
        [[nodiscard]] static Amd64Mov OI(Register &dst, std::vector<std::uint8_t> const &data)
        {
            std::array<std::uint8_t, 8> data_ext = {0, 0, 0, 0, 0, 0, 0, 0};
            std::memcpy(data_ext.data(), data.data(), std::min(data.size(), static_cast<std::size_t>(8)));

            std ::uint8_t opcode = 0xB8 + dst.GetCode();
            return {Amd64Encoding{
                    .rex{{
                            .w = true,
                            .r = dst.IsExtension(),
                    }},
                    .opcode = {opcode},
                    .imm = data_ext,
            }};
        }

        /// MOV(D|Q) xmm, r/m(32|64)
        [[nodiscard]] static Amd64Mov ADQ(Register &dst, Register &src, std::size_t precision = 8, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            return {Amd64Encoding{
                    .legacy_prefix = 0x66,
                    .rex{{
                            .w = precision == 8,
                            .r = dst.IsExtension(),
                            .b = src.IsExtension(),
                    }},
                    .opcode = {0x0F, 0x6E},
                    .mod{{
                            .access = access,
                            .reg_code = dst.GetCode(),
                            .rm_code = src.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        /// MOVS(S|D) xmm1, (xmm2|m(32|64))
        [[nodiscard]] static Amd64Mov AS(Register &dst, Register &src, std::size_t precision = 8, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            std::uint8_t opcode_leader = precision == 8 ? 0xF2 : 0xF3;
            return {Amd64Encoding{
                    .rex{{
                            .r = dst.IsExtension(),
                            .b = src.IsExtension(),
                    }},
                    .opcode = {opcode_leader, 0x0F, 0x10},
                    .mod{{
                            .access = access,
                            .reg_code = dst.GetCode(),
                            .rm_code = src.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        /// MOVS(S|D) xmm2/m(32|64), xmm1
        [[nodiscard]] static Amd64Mov CS(Register &dst, Register &src, std::size_t precision = 8, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            std::uint8_t opcode_leader = precision == 8 ? 0xF2 : 0xF3;
            return {Amd64Encoding{
                    .rex{{
                            .r = src.IsExtension(),
                            .b = dst.IsExtension(),
                    }},
                    .opcode = {opcode_leader, 0x0F, 0x11},
                    .mod{{
                            .access = access,
                            .reg_code = src.GetCode(),
                            .rm_code = dst.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        Amd64Mov(Amd64Encoding encoding) : Amd64Instruction(encoding) {}
    };
} // namespace city

#endif // CITY_AMD64MOVMR64_H
