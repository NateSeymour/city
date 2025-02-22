#ifndef AMD64LEA_H
#define AMD64LEA_H

#include "city/backend/amd64/instruction/Amd64Instruction.h"
#include "city/container/Register.h"

namespace city
{
    class Amd64Lea : public Amd64Instruction
    {
    public:
        [[nodiscard]] static Amd64Lea RM(Register &dst, Register &src, Amd64Access mod = Amd64Access::DisplacedPointer, std::int32_t disp = 0)
        {
            Amd64Lea inst{};

            inst.SetREX(&dst, &src);
            inst.SetOpcode({0x8D});
            inst.SetModRM(dst.GetCode(), src.GetCode(), mod, disp);

            return inst;
        }
    };
} // namespace city

#endif // AMD64LEA_H
