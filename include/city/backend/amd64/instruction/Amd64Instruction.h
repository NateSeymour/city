#ifndef X86_64INSTRUCTION_H
#define X86_64INSTRUCTION_H

#include <cstdint>
#include <optional>
#include "city/ByteBuffer.h"
#include "city/backend/NativeInstruction.h"
#include "city/backend/amd64/Amd64.h"

namespace city
{

    /**
     * Determines the type of access made to into the register.
     * If Pointer, then the value in the register will be treated as a pointer. Instructions will load value from memory location held in pointer.
     * If Value, then the value in the register will be treated as a value.
     */
    enum class Amd64Access : std::uint8_t
    {
        Pointer = 0x0,
        DisplacedPointer = 0x2,
        Value = 0x3,
    };

    struct Amd64REX
    {
        /// Operand size
        bool w = false;

        /// REG extension
        bool r = false;

        /// SIB extension
        bool x = false;

        /// R/M extension
        bool b = false;

        [[nodiscard]] bool ContainsInformation() const noexcept
        {
            return w || r || x || b;
        }

        operator std::uint8_t() const() const noexcept
        {
            return 0b0100'0000 | (w ? 0b1 << 3 : 0) | (r ? 0b1 << 2 : 0) | (x ? 0b1 << 1 : 0) | (b ? 0b1 << 0 : 0);
        }
    };

    struct Amd64Mod
    {
        Amd64Access access;
        std::uint8_t reg_code;
        std::uint8_t rm_code;

        operator std::uint8_t() const() const noexcept
        {
            return (0 | (static_cast<std::uint8_t>(access) << 6) | (reg_code << 3) | rm_code);
        }
    };

    struct Amd64Encoding
    {
        std::optional<std::uint8_t> legacy_prefix = std::nullopt;
        std::optional<Amd64REX> rex = std::nullopt;
        ByteBuffer<3> opcode = {};
        std::optional<Amd64Mod> mod = std::nullopt;
        std::optional<std::uint8_t> sib = std::nullopt;
        std::optional<std::int32_t> disp = std::nullopt;
        std::optional<ByteBuffer<8>> imm = std::nullopt;
    };

    class Amd64Instruction : public NativeInstruction
    {
        Amd64Encoding encoding_;

    public:
        [[nodiscard]] std::size_t GetBinarySize() const noexcept override;
        size_t AppendToBuffer(std::vector<std::uint8_t> &buffer) override;

        Amd64Instruction(Amd64Encoding encoding) : encoding_(encoding) {}
    };

    template<typename InstructionType>
            struct CInstRM : std::bool_constant < requires()
    {
        InstructionType::RMX;
    } > {};

    template<typename InstructionType>
            struct CInstM : std::bool_constant < requires()
    {
        InstructionType::MX;
    } > {};

    template<typename InstructionType>
            struct CInstMI : std::bool_constant < requires()
    {
        InstructionType::MI64;
    } > {};

    template<typename InstructionType>
    concept CInstSDA = requires(InstructionType &inst) { InstructionType::SDA; };

    template<typename InstructionType>
        requires CInstSDA<InstructionType>
    constexpr bool InstHasSDA = true;
} // namespace city

#endif // X86_64INSTRUCTION_H
