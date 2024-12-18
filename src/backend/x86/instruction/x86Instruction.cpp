#include "x86Instruction.h"

using namespace city;

void x86Instruction::SetOpcode(std::initializer_list<std::uint8_t> bytes)
{
    this->opcode_ = bytes;
}

void x86Instruction::SetImmediate(std::initializer_list<std::uint8_t> bytes)
{
    this->immediate_ = bytes;
}

void x86Instruction::SetModRM(x86RegisterCode reg, x86RegisterCode r_m, x86Mod mod)
{
    auto breg = static_cast<std::uint8_t>(reg);
    auto br_m = static_cast<std::uint8_t>(r_m);
    auto bmod = static_cast<std::uint8_t>(mod);

    this->has_mod_rm_ = true;
    this->mod_rm_ = (0 | (bmod << 6) | (breg << 3) | br_m);
}
