#ifndef CITY_AARCH64_H
#define CITY_AARCH64_H

#include <cstdint>
#include "backend/Backend.h"

namespace city
{
    enum class AArch64Register : std::uint8_t
    {
        R0 = 0,
        R1 = 1,
        R2 = 2,
        R3 = 3,
        R4 = 4,
        R5 = 5,
        R6 = 6,
        R7 = 7,
        R8 = 8,
        R9 = 9,
        R10 = 10,
        R11 = 11,
        R12 = 12,
        R13 = 13,
        R14 = 14,
        R15 = 15,
        R16 = 16,
        R17 = 17,
        R18 = 18,
        R19 = 19,
        R20 = 20,
        R21 = 21,
        R22 = 22,
        R23 = 23,
        R24 = 24,
        R25 = 25,
        R26 = 26,
        R27 = 27,
        R28 = 28,
        R29 = 29,
        R30 = 30,
        SP = 31,
    };

    enum class AArch64Condition : std::uint8_t
    {
        EQ = 0b0000,
        NE = 0b0001,
        CS = 0b0010,
        CC = 0b0011,
        MI = 0b0100,
        PL = 0b0101,
        VS = 0b0110,
        VC = 0b0111,
        HI = 0b1000,
        LS = 0b1001,
        GE = 0b1010,
        LT = 0b1011,
        GT = 0b1100,
        LE = 0b1101,
        AL = 0b1110,
        NV = 0b1111,
    };

    class AArch64 : public Backend
    {

    };
} // city

#endif //CITY_AARCH64_H
