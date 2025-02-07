#ifndef X86_64INSTRUCTION_H
#define X86_64INSTRUCTION_H

#include <array>
#include <city/ByteBuffer.h>
#include <city/backend/NativeInstruction.h>
#include <city/backend/amd64/Amd64.h>
#include <cstdint>

namespace city
{
    /**
     * Container to hold x86 maximum prefix size (3 bytes).
     */
    using Amd64Prefix = ByteBuffer<3>;

    /**
     * Container to hold the x86 maximum opcode size (3 bytes).
     */
    using Amd64Opcode = ByteBuffer<3>;

    /**
     * Container to hold the x86 maximum immediate size (8 bytes == 1QW).
     */
    using Amd64Immediate = ByteBuffer<8>;

    /**
     * Determines the type of access made to into the register.
     * If Pointer, then the value in the register will be treated as a pointer. Instructions will load value from memory location held in pointer.
     * If Value, then the value in the register will be treated as a value.
     */
    enum class Amd64Mod : std::uint8_t
    {
        Pointer = 0x0,
        DisplacedPointer = 0x2,
        Value = 0x3,
    };

    class Amd64Instruction : public NativeInstruction
    {
        Amd64Prefix prefix_ = {};
        Amd64Opcode opcode_ = {};

        Amd64Mod mod_ = Amd64Mod::Value;
        bool has_mod_rm_ = false;
        std::uint8_t mod_rm_ = 0x0;

        bool has_sib_ = false;
        std::uint8_t sib_ = 0x0;

        std::int32_t displacement_ = 0;

        Amd64Immediate immediate_ = {};

    public:
        static std::uint8_t const REX_0 = 0b0100'0000;
        static std::uint8_t const REX_W = 0b0000'1000;
        static std::uint8_t const REX_R = 0b0000'0100;
        static std::uint8_t const REX_X = 0b0000'0010;
        static std::uint8_t const REX_B = 0b0000'0001;

        [[nodiscard]] std::size_t GetBinarySize() const noexcept override;
        size_t AppendToBuffer(std::vector<std::uint8_t> &buffer) override;
        [[nodiscard]] std::size_t GetStubOffset() override;

        void SetREX(Amd64Register *reg = nullptr, Amd64Register *rm = nullptr);

        void SetPrefix(std::initializer_list<std::uint8_t> bytes);
        void SetOpcode(std::initializer_list<std::uint8_t> bytes);

        /**
         * Calculates ModR/M byte using formula from section 2.1.5 of architecture reference manual. Also sets displacement for access.
         * @param reg Register (R)
         * @param r_m Register or Memory (R/M)
         * @param mod Addressing Mode
         * @param disp Displacement
         * @return ModR/M
         */
        void SetModRM(std::uint8_t reg, std::uint8_t rm, Amd64Mod mod, std::int32_t disp = 0);

        void SetImmediate(std::initializer_list<std::uint8_t> bytes);
    };
} // namespace city

#endif // X86_64INSTRUCTION_H
