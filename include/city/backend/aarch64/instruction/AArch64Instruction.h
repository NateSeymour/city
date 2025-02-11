#ifndef CITY_AARCH64INSTRUCTION_H
#define CITY_AARCH64INSTRUCTION_H

#include <cstdint>

#include "city/backend/NativeInstruction.h"
#include "city/backend/aarch64/container/AArch64Register.h"

namespace city
{
    class AArch64Instruction : public NativeInstruction
    {
        std::uint32_t encoding_ = 0;

    protected:
        [[nodiscard]] static AArch64Instruction AddSubI(AArch64Register &dst, AArch64Register &src, bool sf = true, bool s = true)
        {
            union
            {
                struct
                {
                    unsigned dst : 5 = 0;
                    unsigned src : 5 = 0;
                    unsigned imm : 12 = 0;
                    unsigned sh : 1 = 0;
                    unsigned op : 6 = 0b100010;
                    unsigned s : 1 = 0;
                    unsigned op1 : 1 = 0;
                    unsigned sf : 1 = 0;
                };

                std::uint32_t raw;
            } encoding{};

            return {encoding.raw};
        }

    public:
        [[nodiscard]] static AArch64Instruction Add(AArch64Instruction &dst, AArch64Instruction &src, bool sf = true, bool s = true) {}

        [[nodiscard]] std::size_t GetStubOffset() override;

        [[nodiscard]] std::size_t GetBinarySize() const noexcept override;

        std::size_t AppendToBuffer(std::vector<std::uint8_t> &buffer) override;

        AArch64Instruction(std::uint32_t encoding) : encoding_(encoding) {}
    };
} // namespace city

#endif // CITY_AARCH64INSTRUCTION_H
