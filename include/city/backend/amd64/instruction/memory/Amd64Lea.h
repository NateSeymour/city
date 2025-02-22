#ifndef AMD64LEA_H
#define AMD64LEA_H

#include "city/backend/amd64/instruction/Amd64Instruction.h"
#include "city/container/Register.h"

namespace city
{
    class Amd64Lea : public Amd64Instruction
    {
    public:
        /// LEA r64, m
        [[nodiscard]] static Amd64Lea RM(Register &dst, Register &src, Amd64Access access = Amd64Access::DisplacedPointer, std::optional<std::int32_t> disp = std::nullopt)
        {
            return {Amd64Encoding{
                    .rex{{
                            .w = true,
                            .r = dst.IsExtension(),
                            .b = src.IsExtension(),
                    }},
                    .opcode = {0x8D},
                    .mod{{
                            .access = access,
                            .reg_code = dst.GetCode(),
                            .rm_code = src.GetCode(),
                    }},
                    .disp = disp,
            }};
        }

        Amd64Lea(Amd64Encoding encoding) : Amd64Instruction(encoding) {}
    };
} // namespace city

#endif // AMD64LEA_H
