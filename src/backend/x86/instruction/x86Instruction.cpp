#include "x86Instruction.h"
#include <cstring>

using namespace city;

size_t x86Instruction::GetBinarySize() const noexcept
{
    std::size_t size = 0;

    size += this->prefix_.GetSize();
    size += this->opcode_.GetSize();
    size += this->has_mod_rm_ ? 1 : 0;
    size += this->has_sib_ ? 1 : 0;
    size += this->immediate_.GetSize();

    return size;
}

size_t x86Instruction::WriteToBuffer(std::byte *buffer) const
{
    std::byte *buffer_it = buffer;

    std::memcpy(buffer_it, this->prefix_.GetBuffer(), this->prefix_.GetSize());
    buffer_it += this->prefix_.GetSize();

    std::memcpy(buffer_it, this->opcode_.GetBuffer(), this->opcode_.GetSize());
    buffer_it += this->opcode_.GetSize();

    if (this->has_mod_rm_)
    {
        std::memcpy(buffer_it, &this->mod_rm_, 1);
        buffer_it++;
    }

    if (this->has_sib_)
    {
        std::memcpy(buffer_it, &this->sib_, 1);
        buffer_it++;
    }

    std::memcpy(buffer_it, this->immediate_.GetBuffer(), this->immediate_.GetSize());
    buffer_it += this->immediate_.GetSize();

    return buffer_it - buffer;
}

void x86Instruction::SetPrefix(std::initializer_list<std::uint8_t> bytes)
{
    this->prefix_ = bytes;
}

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
