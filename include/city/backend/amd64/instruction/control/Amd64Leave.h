#ifndef CITY_AMD64LEAVE_H
#define CITY_AMD64LEAVE_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Leave : public Amd64Instruction
    {
    public:
        /// LEAVE
        [[nodiscard]] static Amd64Leave ZO()
        {
            return {Amd64Encoding{
                    .opcode = {0xC9},
            }};
        }

        Amd64Leave(Amd64Encoding encoding) : Amd64Instruction(encoding) {}
    };
} // namespace city

#endif // CITY_AMD64LEAVE_H
