#ifndef CITY_AMD64CALL_H
#define CITY_AMD64CALL_H

#include <city/backend/amd64/instruction/Amd64Instruction.h>

namespace city
{
    class Amd64Call : public Amd64Instruction
    {
    public:
        static Amd64Call M64(Register &dst, Amd64Mod mod = Amd64Mod::Value, std::int32_t disp = 0) noexcept
        {
            Amd64Call inst;

            inst.SetOpcode({0xFF});
            inst.SetModRM(2, dst.GetCode(), mod, disp);

            return inst;
        }
    };
} // namespace city

#endif // CITY_AMD64CALL_H
