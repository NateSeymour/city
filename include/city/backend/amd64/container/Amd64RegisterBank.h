#ifndef CITY_AMD64REGISTERBANK_H
#define CITY_AMD64REGISTERBANK_H

#include <array>
#include <city/ABI.h>
#include "Amd64Register.h"

namespace city
{
    struct Amd64RegisterBank
    {
#if defined(ABI_SYSV)
        std::array<Amd64Register, 16> r = {
                Amd64Register(0, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, false),    // RAX
                Amd64Register(1, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, false),    // RCX
                Amd64Register(2, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, false),    // RDX
                Amd64Register(3, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::NonVolatile, Amd64RegisterType::GeneralPurpose, false), // RBX
                Amd64Register(4, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::NonVolatile, Amd64RegisterType::Special, false),        // RSP
                Amd64Register(5, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::NonVolatile, Amd64RegisterType::Special, false),        // RBP
                Amd64Register(6, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, false),    // RSI
                Amd64Register(7, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, false),    // RDI
                Amd64Register(0, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, true),     // R8
                Amd64Register(1, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, true),     // R9
                Amd64Register(2, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, true),     // R10
                Amd64Register(3, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, true),     // R11
                Amd64Register(4, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::NonVolatile, Amd64RegisterType::GeneralPurpose, true),  // R12
                Amd64Register(5, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::NonVolatile, Amd64RegisterType::GeneralPurpose, true),  // R13
                Amd64Register(6, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::NonVolatile, Amd64RegisterType::GeneralPurpose, true),  // R14
                Amd64Register(7, Amd64RegisterValueType::Integer, Amd64RegisterVolatility::NonVolatile, Amd64RegisterType::GeneralPurpose, true),  // R15
        };
        std::array<Amd64Register, 16> xmm = {
                Amd64Register(0, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, false), // XMM0
                Amd64Register(1, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, false), // XMM1
                Amd64Register(2, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, false), // XMM2
                Amd64Register(3, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, false), // XMM3
                Amd64Register(4, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, false), // XMM4
                Amd64Register(5, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, false), // XMM5
                Amd64Register(6, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, false), // XMM6
                Amd64Register(7, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, false), // XMM7
                Amd64Register(0, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, true),  // XMM8
                Amd64Register(1, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, true),  // XMM9
                Amd64Register(2, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, true),  // XMM10
                Amd64Register(3, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, true),  // XMM11
                Amd64Register(4, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, true),  // XMM12
                Amd64Register(5, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, true),  // XMM13
                Amd64Register(6, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, true),  // XMM14
                Amd64Register(7, Amd64RegisterValueType::FloatingPoint, Amd64RegisterVolatility::Volatile, Amd64RegisterType::GeneralPurpose, true),  // XMM15
        };
        std::array<Amd64Register *, 9> r_volatile = {
                &this->r[0],
                &this->r[1],
                &this->r[2],
                &this->r[6],
                &this->r[7],
                &this->r[8],
                &this->r[9],
                &this->r[10],
                &this->r[11],
        };
        std::array<Amd64Register *, 16> xmm_volatile = {
                &this->xmm[0],
                &this->xmm[1],
                &this->xmm[2],
                &this->xmm[3],
                &this->xmm[4],
                &this->xmm[5],
                &this->xmm[6],
                &this->xmm[7],
                &this->xmm[8],
                &this->xmm[9],
                &this->xmm[10],
                &this->xmm[11],
                &this->xmm[12],
                &this->xmm[13],
                &this->xmm[14],
                &this->xmm[15],
        };
        std::array<Amd64Register *, 6> r_args = {
                &this->r[7],
                &this->r[6],
                &this->r[2],
                &this->r[4],
                &this->r[8],
                &this->r[9],
        };
        std::array<Amd64Register *, 8> xmm_args = {
                &this->xmm[0],
                &this->xmm[1],
                &this->xmm[2],
                &this->xmm[3],
                &this->xmm[4],
                &this->xmm[5],
                &this->xmm[6],
                &this->xmm[7],
        };
#endif
    };
} // namespace city

#endif // CITY_AMD64REGISTERBANK_H
