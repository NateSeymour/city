#ifndef CITY_RegisterBANK_H
#define CITY_RegisterBANK_H

#include <array>
#include "city/ABI.h"
#include "city/container/Register.h"

namespace city
{
    struct Amd64RegisterBank
    {
#if defined(ABI_SYSV)
        std::array<Register, 16> r = {
                Register(0, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, false),    // RAX
                Register(1, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, false),    // RCX
                Register(2, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, false),    // RDX
                Register(3, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::General, false), // RBX
                Register(4, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::Special, false), // RSP
                Register(5, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::Special, false), // RBP/RIP
                Register(6, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, false),    // RSI
                Register(7, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, false),    // RDI
                Register(0, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, true),     // R8
                Register(1, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, true),     // R9
                Register(2, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, true),     // R10
                Register(3, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, true),     // R11
                Register(4, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::General, true),  // R12
                Register(5, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::General, true),  // R13
                Register(6, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::General, true),  // R14
                Register(7, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::General, true),  // R15
        };
        std::array<Register, 16> xmm = {
                Register(0, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false), // XMM0
                Register(1, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false), // XMM1
                Register(2, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false), // XMM2
                Register(3, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false), // XMM3
                Register(4, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false), // XMM4
                Register(5, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false), // XMM5
                Register(6, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false), // XMM6
                Register(7, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false), // XMM7
                Register(0, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, true),  // XMM8
                Register(1, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, true),  // XMM9
                Register(2, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, true),  // XMM10
                Register(3, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, true),  // XMM11
                Register(4, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, true),  // XMM12
                Register(5, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, true),  // XMM13
                Register(6, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, true),  // XMM14
                Register(7, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, true),  // XMM15
        };
        std::array<Register *, 9> r_volatile = {
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
        std::array<Register *, 16> xmm_volatile = {
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
        std::array<Register *, 6> r_args = {
                &this->r[7],
                &this->r[6],
                &this->r[2],
                &this->r[4],
                &this->r[8],
                &this->r[9],
        };
        std::array<Register *, 8> xmm_args = {
                &this->xmm[0],
                &this->xmm[1],
                &this->xmm[2],
                &this->xmm[3],
                &this->xmm[4],
                &this->xmm[5],
                &this->xmm[6],
                &this->xmm[7],
        };
#elif defined(ABI_WINDOWS)
        std::array<Register, 16> r = {
                Register(0, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, false),    // RAX
                Register(1, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, false),    // RCX
                Register(2, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, false),    // RDX
                Register(3, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::General, false), // RBX
                Register(4, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::Special, false), // RSP
                Register(5, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::Special, false), // RBP
                Register(6, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::General, false), // RSI
                Register(7, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::General, false), // RDI
                Register(0, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, true),     // R8
                Register(1, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, true),     // R9
                Register(2, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, true),     // R10
                Register(3, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::General, true),     // R11
                Register(4, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::General, true),  // R12
                Register(5, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::General, true),  // R13
                Register(6, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::General, true),  // R14
                Register(7, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::General, true),  // R15
        };
        std::array<Register, 16> xmm = {
                Register(0, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false),    // XMM0
                Register(1, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false),    // XMM1
                Register(2, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false),    // XMM2
                Register(3, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false),    // XMM3
                Register(4, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false),    // XMM4
                Register(5, RegisterType::FloatingPoint, Volatility::Volatile, RegisterPurpose::General, false),    // XMM5
                Register(6, RegisterType::FloatingPoint, Volatility::NonVolatile, RegisterPurpose::General, false), // XMM6
                Register(7, RegisterType::FloatingPoint, Volatility::NonVolatile, RegisterPurpose::General, false), // XMM7
                Register(0, RegisterType::FloatingPoint, Volatility::NonVolatile, RegisterPurpose::General, true),  // XMM8
                Register(1, RegisterType::FloatingPoint, Volatility::NonVolatile, RegisterPurpose::General, true),  // XMM9
                Register(2, RegisterType::FloatingPoint, Volatility::NonVolatile, RegisterPurpose::General, true),  // XMM10
                Register(3, RegisterType::FloatingPoint, Volatility::NonVolatile, RegisterPurpose::General, true),  // XMM11
                Register(4, RegisterType::FloatingPoint, Volatility::NonVolatile, RegisterPurpose::General, true),  // XMM12
                Register(5, RegisterType::FloatingPoint, Volatility::NonVolatile, RegisterPurpose::General, true),  // XMM13
                Register(6, RegisterType::FloatingPoint, Volatility::NonVolatile, RegisterPurpose::General, true),  // XMM14
                Register(7, RegisterType::FloatingPoint, Volatility::NonVolatile, RegisterPurpose::General, true),  // XMM15
        };
        std::array<Register *, 7> r_volatile = {
                &this->r[0],
                &this->r[1],
                &this->r[2],
                &this->r[8],
                &this->r[9],
                &this->r[10],
                &this->r[11],
        };
        std::array<Register *, 6> xmm_volatile = {
                &this->xmm[0],
                &this->xmm[1],
                &this->xmm[2],
                &this->xmm[3],
                &this->xmm[4],
                &this->xmm[5],
        };
        std::array<Register *, 4> r_args = {
                &this->r[1],
                &this->r[2],
                &this->r[8],
                &this->r[9],
        };
        std::array<Register *, 4> xmm_args = {
                &this->xmm[0],
                &this->xmm[1],
                &this->xmm[2],
                &this->xmm[3],
        };
#endif
    };
} // namespace city

#endif // CITY_RegisterBANK_H
