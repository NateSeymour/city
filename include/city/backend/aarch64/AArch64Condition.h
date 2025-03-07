#ifndef AARCH64CONDITION_H
#define AARCH64CONDITION_H

#include <cstdint>
#include <map>

#include "city/ir/IRCondition.h"

namespace city
{
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

        AL = 0b1111,
    };

    extern std::map<BinaryCondition, AArch64Condition> const AArch64ConditionTranslationMap;
} // namespace city

#endif // AARCH64CONDITION_H
