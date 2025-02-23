#ifndef AMD64XOR_H
#define AMD64XOR_H

#include "city/backend/amd64/instruction/Amd64Instruction.h"
#include "city/container/Register.h"

namespace city
{
    class Amd64Xor : public Amd64Instruction
    {
    public:
        /// XOR r64, r/m64
        [[nodiscard]] static Amd64Xor RM(Register &dst, Register &src, Amd64Access access = Amd64Access::Value, std::optional<std::int32_t> disp = std::nullopt)
        {
            return {Amd64Encoding{
                    .rex{{
                            .w = true,
                            .r = dst.IsExtension(),
                            .b = src.IsExtension(),
                    }},
                    .opcode = {0x33},
                    .mod{{
                            .access = access,
                            .reg_code = dst.GetCode(),
                            .rm_code = src.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        Amd64Xor(Amd64Encoding encoding) : Amd64Instruction(encoding) {}
    };
} // namespace city

#endif // AMD64XOR_H
