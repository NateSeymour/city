#ifndef X86_64INSTRUCTION_H
#define X86_64INSTRUCTION_H

#include <array>
#include <cstdint>
#include "ByteBuffer.h"
#include "backend/NativeInstruction.h"
#include "backend/x86/x86.h"

namespace city
{
    /**
     * Container to hold x86 maximum prefix size (3 bytes).
     */
    using x86Prefix = ByteBuffer<3>;

    enum class Amd64PrefixCode : std::uint8_t
    {
        REXW = 0b0100'1000,
    };

    /**
     * Container to hold the x86 maximum opcode size (3 bytes).
     */
    using x86Opcode = ByteBuffer<3>;

    /**
     * Container to hold the x86 maximum immediate size (8 bytes == 1QW).
     */
    using x86Immediate = ByteBuffer<8>;

    class x86Instruction : public NativeInstruction
    {
        x86Prefix prefix_ = {};
        x86Opcode opcode_ = {};

        bool has_mod_rm_ = false;
        std::uint8_t mod_rm_ = 0x0;

        bool has_sib_ = false;
        std::uint8_t sib_ = 0x0;

        x86Immediate immediate_ = {};

    public:
        [[nodiscard]] size_t GetBinarySize() const noexcept override;
        [[nodiscard]] size_t WriteToBuffer(std::byte *buffer) const override;

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
        void SetModRM(x86RegisterCode reg, x86RegisterCode r_m, x86Mod mod);
    };
} // namespace city

#endif // X86_64INSTRUCTION_H
