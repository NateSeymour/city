#include "x86.h"

using namespace city;

constexpr std::uint8_t x86::CalculateModRM(x86Register reg, x86Register rem, x86Mod mod)
{
    auto breg = static_cast<std::uint8_t>(reg);
    auto brem = static_cast<std::uint8_t>(rem);
    auto bmod = static_cast<std::uint8_t>(mod);

    return (0 | (bmod << 6) | (breg << 3) | brem);
}
