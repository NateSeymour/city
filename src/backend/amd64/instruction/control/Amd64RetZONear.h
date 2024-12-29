#ifndef CITY_AMD64RETZONEAR_H
#define CITY_AMD64RETZONEAR_H

#include "backend/amd64/instruction/Amd64Instruction.h"

namespace city
{
    class Amd46RetZONear : public Amd64Instruction
    {
    public:
        Amd46RetZONear()
        {
            this->SetOpcode({0xC3});
        }
    };
} // namespace city

#endif // CITY_AMD64RETZONEAR_H
