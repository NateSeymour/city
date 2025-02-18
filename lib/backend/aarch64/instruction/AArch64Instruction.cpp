#include "city/backend/aarch64/instruction/AArch64Instruction.h"

using namespace city;

std::size_t AArch64Instruction::GetBinarySize() const noexcept
{
    return 4;
}

std::size_t AArch64Instruction::AppendToBuffer(std::vector<std::uint8_t> &buffer)
{
    auto encoding_buffer = reinterpret_cast<std::uint8_t *>(&this->encoding_);

    buffer.insert(buffer.end(), encoding_buffer, encoding_buffer + 4);

    return 4;
}
