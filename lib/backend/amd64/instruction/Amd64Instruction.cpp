#include <city/backend/amd64/instruction/Amd64Instruction.h>
#include <cstring>
#include <ranges>

using namespace city;

size_t Amd64Instruction::GetBinarySize() const noexcept
{
    std::size_t size = 0;

    size += this->prefix_.GetSize();
    size += this->opcode_.GetSize();
    size += this->has_mod_rm_ ? 1 : 0;
    size += this->has_sib_ ? 1 : 0;
    size += this->immediate_.GetSize();

    return size;
}

size_t Amd64Instruction::AppendToBuffer(std::vector<std::uint8_t> &buffer)
{
    buffer.append_range(this->prefix_);
    buffer.append_range(this->opcode_);

    if (this->has_mod_rm_)
    {
        buffer.push_back(this->mod_rm_);
    }

    if (this->has_sib_)
    {
        buffer.push_back(this->sib_);
    }

    buffer.append_range(this->immediate_);
    return this->GetBinarySize();
}

std::size_t Amd64Instruction::GetStubOffset()
{
    return this->GetBinarySize() - this->immediate_.GetSize();
}

void Amd64Instruction::SetPrefix(std::initializer_list<std::uint8_t> bytes)
{
    this->prefix_ = bytes;
}

void Amd64Instruction::SetOpcode(std::initializer_list<std::uint8_t> bytes)
{
    this->opcode_ = bytes;
}

void Amd64Instruction::SetImmediate(std::initializer_list<std::uint8_t> bytes)
{
    this->immediate_ = bytes;
}

void Amd64Instruction::SetModRM(Amd64RegisterCode reg, Amd64RegisterCode r_m, Amd64Mod mod)
{
    auto breg = static_cast<std::uint8_t>(reg);
    auto br_m = static_cast<std::uint8_t>(r_m);
    auto bmod = static_cast<std::uint8_t>(mod);

    this->has_mod_rm_ = true;
    this->mod_rm_ = (0 | (bmod << 6) | (breg << 3) | br_m);
}
