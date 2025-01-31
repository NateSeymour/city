#ifndef CITY_AMD64REGISTERBANK_H
#define CITY_AMD64REGISTERBANK_H

#include <array>
#include "Amd64Register.h"

namespace city
{
    struct Amd64RegisterBank
    {
        std::array<Amd64Register, 16> r = {
                Amd64Register(0, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(1, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(2, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(3, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(4, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(5, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(6, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(7, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(8, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(9, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(10, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(11, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(12, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(13, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(14, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(15, Amd64RegisterValueType::Integer, Amd64RegisterType::GeneralPurpose, true),
        };
        std::array<Amd64Register, 16> xmm = {
                Amd64Register(0, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(1, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(2, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(3, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(4, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(5, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(6, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(7, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, false),
                Amd64Register(8, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(9, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(10, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(11, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(12, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(13, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(14, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, true),
                Amd64Register(15, Amd64RegisterValueType::FloatingPoint, Amd64RegisterType::GeneralPurpose, true),
        };
    };
} // namespace city

#endif // CITY_AMD64REGISTERBANK_H
