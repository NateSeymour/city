#ifndef X86_64INSTRUCTION_H
#define X86_64INSTRUCTION_H

#include <array>
#include <city/ByteBuffer.h>
#include <city/backend/NativeInstruction.h>
#include <city/backend/amd64/Amd64.h>
#include <city/backend/amd64/container/Amd64ModRM.h>
#include <cstdint>

namespace city
{
    /**
     * Container to hold x86 maximum prefix size (3 bytes).
     */
    using Amd64Prefix = ByteBuffer<3>;

    enum class Amd64PrefixCode : std::uint8_t
    {
        REXW = 0b0100'1000,
    };

    /**
     * Container to hold the x86 maximum opcode size (3 bytes).
     */
    using Amd64Opcode = ByteBuffer<3>;

    /**
     * Container to hold the x86 maximum immediate size (8 bytes == 1QW).
     */
    using Amd64Immediate = ByteBuffer<8>;

    class Amd64Instruction : public NativeInstruction
    {
        Amd64Prefix prefix_ = {};
        Amd64Opcode opcode_ = {};

        bool has_mod_rm_ = false;
        std::uint8_t mod_rm_ = 0x0;

        bool has_sib_ = false;
        std::uint8_t sib_ = 0x0;

        Amd64Immediate immediate_ = {};

    public:
        [[nodiscard]] std::size_t GetBinarySize() const noexcept override;
        size_t AppendToBuffer(std::vector<std::uint8_t> &buffer) override;
        [[nodiscard]] std::size_t GetStubOffset() override;

        void SetPrefix(std::initializer_list<std::uint8_t> bytes);
        void SetOpcode(std::initializer_list<std::uint8_t> bytes);
        void SetImmediate(std::initializer_list<std::uint8_t> bytes);

        /**
         * Calculates ModR/M byte using formula from section 2.1.5 of architecture reference manual.
         * @param reg Register (R)
         * @param r_m Register or Memory (R/M)
         * @param mod Addressing Mode
         * @return ModR/M
         */
        void SetModRM(Amd64RegisterCode reg, Amd64RegisterCode r_m, Amd64Mod mod);
    };
} // namespace city

#endif // X86_64INSTRUCTION_H
