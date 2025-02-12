#include "city/backend/amd64/instruction/Amd64Instruction.h"
#include "city/container/Register.h"

using namespace city;

size_t Amd64Instruction::GetBinarySize() const noexcept
{
    std::size_t size = 0;

    size += this->prefix_.GetSize();
    size += this->opcode_.GetSize();
    size += this->has_mod_rm_ ? 1 : 0;
    size += this->has_sib_ ? 1 : 0;

    if (this->mod_ == Amd64Mod::DisplacedPointer)
    {
        size += 4;
    }

    size += this->immediate_.GetSize();

    return size;
}

size_t Amd64Instruction::AppendToBuffer(std::vector<std::uint8_t> &buffer)
{
    buffer.insert(buffer.end(), this->prefix_.begin(), this->prefix_.end());
    buffer.insert(buffer.end(), this->opcode_.begin(), this->opcode_.end());

    if (this->has_mod_rm_)
    {
        buffer.push_back(this->mod_rm_);
    }

    if (this->has_sib_)
    {
        buffer.push_back(this->sib_);
    }

    if (this->mod_ == Amd64Mod::DisplacedPointer)
    {
        auto disp_buffer = reinterpret_cast<std::uint8_t *>(&this->displacement_);
        buffer.insert(buffer.end(), disp_buffer, disp_buffer + 4);
    }

    buffer.insert(buffer.end(), this->immediate_.begin(), this->immediate_.end());

    return this->GetBinarySize();
}

std::size_t Amd64Instruction::GetStubOffset()
{
    return this->GetBinarySize() - this->immediate_.GetSize();
}

void Amd64Instruction::SetREX(Register *reg, Register *rm)
{
    std::uint8_t prefix = Amd64Instruction::REX_0;
    prefix |= Amd64Instruction::REX_W;

    if (reg && reg->IsExtension())
    {
        prefix |= Amd64Instruction::REX_R;
    }

    if (rm && rm->IsExtension())
    {
        prefix |= Amd64Instruction::REX_B;
    }

    this->SetPrefix({prefix});
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

void Amd64Instruction::SetModRM(std::uint8_t reg, std::uint8_t rm, Amd64Mod mod, std::int32_t disp)
{
    auto breg = reg;
    auto brm = rm;
    auto bmod = static_cast<std::uint8_t>(mod);

    this->has_mod_rm_ = true;
    this->mod_rm_ = (0 | (bmod << 6) | (breg << 3) | brm);

    this->mod_ = mod;
    this->displacement_ = disp;
}
