#ifndef CITY_AMD64RETZONEAR_H
#define CITY_AMD64RETZONEAR_H

#include "backend/x86/instruction/x86Instruction.h"

namespace city
{
    class Amd46RetZONear : public x86Instruction
    {
    public:
        Amd46RetZONear()
        {
            this->SetOpcode({0xC3});
        }
    };
} // namespace city

#endif // CITY_AMD64RETZONEAR_H
