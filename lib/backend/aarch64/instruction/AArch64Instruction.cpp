#include "city/backend/aarch64/instruction/AArch64Instruction.h"
#include "city/overload.h"

using namespace city;

std::size_t AArch64Instruction::GetBinarySize() const noexcept
{
    return 4;
}

std::size_t AArch64Instruction::AppendToBuffer(std::vector<std::uint8_t> &buffer)
{
    auto encoding = std::visit(AArch64EncBinaryExtractor{}, this->encoding_);
    auto encoding_buffer = reinterpret_cast<std::uint8_t *>(&encoding);

    buffer.insert(buffer.end(), encoding_buffer, encoding_buffer + 4);

    return 4;
}

void AArch64Instruction::SetPCRelativeTarget(std::size_t pc)
{
    std::visit(
            overload{
                    [&](AArch64EncCBI &enc) { enc.imm = (pc - enc.imm) / 4; },
            },
            this->encoding_);
}
