#ifndef X86_64_H
#define X86_64_H

#include <cstdint>
#include "backend/Backend.h"

namespace city
{
    enum class x86Mod : std::uint8_t
    {
        Memory = 0x0,
        MemoryD8 = 0x1,
        MemoryD32 = 0x2,
        Register = 0x3,
    };

    enum class x86Register : std::uint8_t
    {
        AL = 0x0,
        AX = 0x0,
        EAX = 0x0,
        MM0 = 0x0,
        XMM0 = 0x0,

        CL = 0x1,
        CX = 0x1,
        ECX = 0x1,
        MM1 = 0x1,
        XMM1 = 0x1,

        DL = 0x2,
        DX = 0x2,
        EDX = 0x2,
        MM2 = 0x2,
        XMM2 = 0x2,

        BL = 0x3,
        BX = 0x3,
        EBX = 0x3,
        MM3 = 0x3,
        XMM3 = 0x3,

        AH = 0x4,
        SP = 0x4,
        ESP = 0x4,
        MM4 = 0x4,
        XMM4 = 0x4,

        CH = 0x5,
        BP = 0x5,
        EBP = 0x5,
        MM5 = 0x5,
        XMM5 = 0x5,

        DH = 0x6,
        SI = 0x6,
        ESI = 0x6,
        MM6 = 0x6,
        XMM6 = 0x6,

        BH = 0x7,
        DI = 0x7,
        EDI = 0x7,
        MM7 = 0x7,
        XMM7 = 0x7,
    };

    class x86 : public Backend
    {
    public:
        /**
         * Calculates ModR/M byte using formula from section 2.1.5 of architecture reference manual.
         * @param reg Register (R)
         * @param rem Register or Memory (R/M)
         * @param mod Addressing Mode
         * @return ModR/M
         */
        constexpr static std::uint8_t CalculateModRM(x86Register reg, x86Register rem, x86Mod mod);
    };
} // namespace city

#endif // X86_64_H
