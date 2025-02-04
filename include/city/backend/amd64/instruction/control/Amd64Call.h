#ifndef CITY_AMD64CALL_H
#define CITY_AMD64CALL_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Call : public Amd64Instruction
    {
    public:
        static Amd64Call M64(Amd64RegisterCode reg, Amd64RegisterAccessType mod) noexcept
        {
            Amd64Call inst;

            inst.SetOpcode({0xFF});
            inst.SetModRM(static_cast<Amd64RegisterCode>(2), reg, mod);

            return inst;
        }
    };
} // namespace city

#endif // CITY_AMD64CALL_H
