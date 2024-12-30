#ifndef CITY_AMD64RETZONEAR_H
#define CITY_AMD64RETZONEAR_H

#include "backend/amd64/instruction/Amd64Instruction.h"

namespace city
{
    class Amd64Ret : public Amd64Instruction
    {
    public:
        static constexpr Amd64Ret ZONear() noexcept
        {
            Amd64Ret inst;

            inst.SetOpcode({0xC3});

            return inst;
        }

        static constexpr Amd64Ret ZOFar() noexcept
        {
            Amd64Ret inst;

            inst.SetOpcode({0xCB});

            return inst;
        }
    };
} // namespace city

#endif // CITY_AMD64RETZONEAR_H
