#ifndef AMD64CQO_H
#define AMD64CQO_H
#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Cqo : public Amd64Instruction
    {
    public:
        /// CQO
        /// RDX:RAX:= sign-extend of RAX.
        [[nodiscard]] static Amd64Cqo ZO()
        {
            return {Amd64Encoding{
                    .rex{{
                            .w = true,
                    }},
                    .opcode = {0x99},
            }};
        }

        Amd64Cqo(Amd64Encoding encoding) : Amd64Instruction(encoding) {}
    };
} // namespace city

#endif // AMD64CQO_H
