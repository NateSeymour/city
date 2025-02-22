#ifndef CITY_AMD64CALL_H
#define CITY_AMD64CALL_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Call : public Amd64Instruction
    {
    public:
        /// CALL rel32
        [[nodiscard]] static Amd64Call D(std::int32_t offset)
        {
            return {Amd64Encoding{
                    .opcode = {0xE8},
                    .imm = offset,
            }};
        }

        /// CALL m16:64
        [[nodiscard]] static Amd64Call M(Register &dst, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt) noexcept
        {
            return {Amd64Encoding{
                    .rex{{
                            .w = true,
                            .b = dst.IsExtension(),
                    }},
                    .opcode = {0xFF},
                    .mod{{
                            .access = access,
                            .reg_code = 3,
                            .rm_code = dst.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        Amd64Call(Amd64Encoding encoding) : Amd64Instruction(encoding) {}
    };
} // namespace city

#endif // CITY_AMD64CALL_H
