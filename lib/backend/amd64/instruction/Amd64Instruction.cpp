#include "city/backend/amd64/instruction/Amd64Instruction.h"
#include "city/container/Register.h"

using namespace city;

size_t Amd64Instruction::GetBinarySize() const noexcept
{
    std::size_t size = 0;

    if (this->encoding_.legacy_prefix.has_value())
    {
        size++;
    }
    if (this->encoding_.rex.has_value() && this->encoding_.rex->ContainsInformation())
    {
        size++;
    }

    size += this->encoding_.opcode.GetSize();

    if (this->encoding_.mod.has_value())
    {
        size++;
    }
    if (this->encoding_.disp.has_value())
    {
        size += 4;
    }
    if (this->encoding_.imm.has_value())
    {
        size += this->encoding_.imm->GetSize();
    }

    return size;
}

size_t Amd64Instruction::AppendToBuffer(std::vector<std::uint8_t> &buffer)
{
    if (this->encoding_.legacy_prefix.has_value())
    {
        buffer.push_back(*this->encoding_.legacy_prefix);
    }
    if (this->encoding_.rex.has_value() && this->encoding_.rex->ContainsInformation())
    {
        buffer.push_back(*this->encoding_.rex);
    }

    buffer.insert(buffer.end(), this->encoding_.opcode.begin(), this->encoding_.opcode.end());

    if (this->encoding_.mod.has_value())
    {
        buffer.push_back(*this->encoding_.mod);
    }
    if (this->encoding_.sib.has_value())
    {
        buffer.push_back(*this->encoding_.sib);
    }
    if (this->encoding_.disp.has_value())
    {
        auto disp_buffer = reinterpret_cast<std::uint8_t *>(&this->encoding_.disp.value());
        buffer.insert(buffer.end(), disp_buffer, disp_buffer + 4);
    }
    if (this->encoding_.imm.has_value())
    {
        buffer.insert(buffer.end(), this->encoding_.imm->begin(), this->encoding_.imm->end());
    }

    return this->GetBinarySize();
}
