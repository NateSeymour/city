#ifndef AARCH64REGISTERBANK_H
#define AARCH64REGISTERBANK_H

#include <array>
#include "city/container/Register.h"

namespace city
{
    struct AArch64RegisterBank
    {
        std::array<Register, 32> r = {
                Register(0, RegisterType::Integer, Volatility::Volatile),
                Register(1, RegisterType::Integer, Volatility::Volatile),
                Register(2, RegisterType::Integer, Volatility::Volatile),
                Register(3, RegisterType::Integer, Volatility::Volatile),
                Register(4, RegisterType::Integer, Volatility::Volatile),
                Register(5, RegisterType::Integer, Volatility::Volatile),
                Register(6, RegisterType::Integer, Volatility::Volatile),
                Register(7, RegisterType::Integer, Volatility::Volatile),
                Register(8, RegisterType::Integer, Volatility::Volatile),
                Register(9, RegisterType::Integer, Volatility::Volatile),
                Register(10, RegisterType::Integer, Volatility::Volatile),
                Register(11, RegisterType::Integer, Volatility::Volatile),
                Register(12, RegisterType::Integer, Volatility::Volatile),
                Register(13, RegisterType::Integer, Volatility::Volatile),
                Register(14, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::Special),    // SUBROUTINE LINK
                Register(15, RegisterType::Integer, Volatility::Volatile, RegisterPurpose::Special),    // STUB BASE
                Register(16, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::Special), // IP0
                Register(17, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::Special), // IP1
                Register(18, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::Special), // PR
                Register(19, RegisterType::Integer, Volatility::NonVolatile),
                Register(20, RegisterType::Integer, Volatility::NonVolatile),
                Register(21, RegisterType::Integer, Volatility::NonVolatile),
                Register(22, RegisterType::Integer, Volatility::NonVolatile),
                Register(23, RegisterType::Integer, Volatility::NonVolatile),
                Register(24, RegisterType::Integer, Volatility::NonVolatile),
                Register(25, RegisterType::Integer, Volatility::NonVolatile),
                Register(26, RegisterType::Integer, Volatility::NonVolatile),
                Register(27, RegisterType::Integer, Volatility::NonVolatile),
                Register(28, RegisterType::Integer, Volatility::NonVolatile),
                Register(29, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::Special), // FP
                Register(30, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::Special), // LR
                Register(31, RegisterType::Integer, Volatility::NonVolatile, RegisterPurpose::Special), // ZR
        };
        std::array<Register *, 16> r_volatile = {
                &this->r[0],
                &this->r[1],
                &this->r[2],
                &this->r[3],
                &this->r[4],
                &this->r[5],
                &this->r[6],
                &this->r[7],
                &this->r[8],
                &this->r[9],
                &this->r[10],
                &this->r[11],
                &this->r[12],
                &this->r[13],
                &this->r[14],
                &this->r[15],
        };
        std::array<Register *, 8> r_args = {
                &this->r[0],
                &this->r[1],
                &this->r[2],
                &this->r[3],
                &this->r[4],
                &this->r[5],
                &this->r[6],
                &this->r[7],
        };
        std::array<Register, 32> v = {
                Register(0, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(1, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(2, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(3, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(4, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(5, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(6, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(7, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(8, RegisterType::FloatingPoint, Volatility::NonVolatile),
                Register(9, RegisterType::FloatingPoint, Volatility::NonVolatile),
                Register(10, RegisterType::FloatingPoint, Volatility::NonVolatile),
                Register(11, RegisterType::FloatingPoint, Volatility::NonVolatile),
                Register(12, RegisterType::FloatingPoint, Volatility::NonVolatile),
                Register(13, RegisterType::FloatingPoint, Volatility::NonVolatile),
                Register(14, RegisterType::FloatingPoint, Volatility::NonVolatile),
                Register(15, RegisterType::FloatingPoint, Volatility::NonVolatile),
                Register(16, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(17, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(18, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(19, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(20, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(21, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(22, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(23, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(24, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(25, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(26, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(27, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(28, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(29, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(30, RegisterType::FloatingPoint, Volatility::Volatile),
                Register(31, RegisterType::FloatingPoint, Volatility::Volatile),
        };
        std::array<Register *, 24> v_volatile = {
                &this->v[0],
                &this->v[1],
                &this->v[2],
                &this->v[3],
                &this->v[4],
                &this->v[5],
                &this->v[6],
                &this->v[7],
                &this->v[16],
                &this->v[17],
                &this->v[18],
                &this->v[19],
                &this->v[20],
                &this->v[21],
                &this->v[22],
                &this->v[23],
                &this->v[24],
                &this->v[25],
                &this->v[26],
                &this->v[27],
                &this->v[28],
                &this->v[29],
                &this->v[30],
                &this->v[31],
        };
        std::array<Register *, 8> v_args = {
                &this->v[0],
                &this->v[1],
                &this->v[2],
                &this->v[3],
                &this->v[4],
                &this->v[5],
                &this->v[6],
                &this->v[7],
        };
    };
} // namespace city

#endif // AARCH64REGISTERBANK_H
