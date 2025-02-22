#ifndef CITY_AMD64RETZONEAR_H
#define CITY_AMD64RETZONEAR_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Ret : public Amd64Instruction
    {
    public:
        /// RET
        [[nodiscard]] static Amd64Ret ZONear() noexcept
        {
            return {Amd64Encoding{
                    .opcode = {0xC3},
            }};
        }

        Amd64Ret(Amd64Encoding encoding) : Amd64Instruction(encoding) {}
    };
} // namespace city

#endif // CITY_AMD64RETZONEAR_H
