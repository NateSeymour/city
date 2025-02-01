#ifndef CITY_AMD64LEAVE_H
#define CITY_AMD64LEAVE_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Leave : public Amd64Instruction
    {
    public:
        static constexpr Amd64Leave ZO()
        {
            Amd64Leave inst;

            inst.SetOpcode({0xC9});

            return inst;
        }
    };
} // namespace city

#endif // CITY_AMD64LEAVE_H
