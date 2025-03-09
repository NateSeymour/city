#ifndef CITY_AARCH64INSTRUCTION_H
#define CITY_AARCH64INSTRUCTION_H

#include <cstdint>
#include <variant>
#include "city/backend/NativeInstruction.h"

namespace city
{
    /// Data Processing Add/Sub (Immediate)
    struct AArch64EncDPASI
    {
        unsigned rd : 5 = 0b0;
        unsigned rn : 5 = 0b0;
        unsigned imm : 12 = 0b0;
        unsigned sh : 1 = 0b0;
        unsigned op0 : 6 = 0b1000'10;
        unsigned s : 1 = 0b0;
        unsigned op : 1 = 0b0;
        unsigned sf : 1 = 0b1;
    };
    static_assert(sizeof(AArch64EncDPASI) == 4);

    /// Data Processing Add/Sub (Extended Register)
    struct AArch64EncDPASE
    {
        unsigned rd : 5 = 0b0;
        unsigned rn : 5 = 0b0;
        unsigned imm : 3 = 0b0;
        unsigned option : 3 = 0b0;
        unsigned rm : 5 = 0b0;
        unsigned _0 : 1 = 0b1;
        unsigned opt : 2 = 0b0;
        unsigned op0 : 5 = 0b0101'1;
        unsigned s : 1 = 0b0;
        unsigned op : 1 = 0b0;
        unsigned sf : 1 = 0b1;
    };
    static_assert(sizeof(AArch64EncDPASE) == 4);

    /// Data Processing Add/Sub (Shifted Register)
    struct AArch64DPASS
    {
        unsigned rd : 5 = 0b0;
        unsigned rn : 5 = 0b0;
        unsigned imm : 6 = 0b0;
        unsigned rm : 5 = 0b0;
        unsigned _0 : 1 = 0b0;
        unsigned shift : 2 = 0b0;
        unsigned op0 : 5 = 0b0101'1;
        unsigned s : 1 = 0b0;
        unsigned op : 1 = 0b0;
        unsigned sf : 1 = 0b1;
    };
    static_assert(sizeof(AArch64DPASS) == 4);

    /// Data Processing Move (Immediate)
    struct AArch64EncDPMI
    {
        unsigned rd : 5 = 0b0;
        unsigned imm : 16 = 0b0;
        unsigned hw : 2 = 0b0;
        unsigned op0 : 6 = 0b1001'01;
        unsigned opc : 2 = 0b0;
        unsigned sf : 1 = 0b1;
    };
    static_assert(sizeof(AArch64EncDPMI) == 4);

    /// Data Processing Bitfield (Immediate)
    struct AArch64EncDPBI
    {
        unsigned rd : 5 = 0b0;
        unsigned rn : 5 = 0b0;
        unsigned imms : 6 = 0b0;
        unsigned immr : 6 = 0b0;
        unsigned n : 1 = 0b0;
        unsigned op0 : 6 = 0b1001'10;
        unsigned opc : 2 = 0b0;
        unsigned sf : 1 = 0b1;
    };
    static_assert(sizeof(AArch64EncDPBI) == 4);

    /// Data Processing (PC-Relative)
    struct AArch64EncDPPCR
    {
        unsigned rd : 5 = 0b0;
        unsigned immhi : 19 = 0b0;
        unsigned op0 : 5 = 0b1000'0;
        unsigned immlo : 2 = 0b0;
        unsigned op : 1 = 0b0;
    };
    static_assert(sizeof(AArch64EncDPPCR) == 4);

    /// Data Processing (2 Sources)
    struct AArch64EncDP2
    {
        unsigned rd : 5 = 0b0;
        unsigned rn : 5 = 0b0;
        unsigned opcode : 6 = 0b0;
        unsigned rm : 5 = 0b0;
        unsigned op0 : 8 = 0b1101'0110;
        unsigned s : 1 = 0b0;
        unsigned _0 : 1 = 0b0;
        unsigned sf : 1 = 0b1;
    };
    static_assert(sizeof(AArch64EncDP2) == 4);

    /// Data Processing (3 Sources)
    struct AArch64EncDP3
    {
        unsigned rd : 5 = 0b0;
        unsigned rn : 5 = 0b0;
        unsigned ra : 5 = 0b0;
        unsigned op : 1 = 0b0;
        unsigned rm : 5 = 0b0;
        unsigned op31 : 3 = 0b0;
        unsigned op0 : 5 = 0b1101'1;
        unsigned op54 : 2 = 0b0;
        unsigned sf : 1 = 0b1;
    };
    static_assert(sizeof(AArch64EncDP3) == 4);

    struct AArch64EncDPL
    {
        unsigned rd : 5 = 0b0;
        unsigned rn : 5 = 0b0;
        unsigned imm : 6 = 0b0;
        unsigned rm : 5 = 0b0;
        unsigned n : 1 = 0b0;
        unsigned shift : 2 = 0b0;
        unsigned op0 : 5 = 0b0101'0;
        unsigned opc : 2 = 0b0;
        unsigned sf : 1 = 0b1;
    };
    static_assert(sizeof(AArch64EncDPL) == 4);

    /// Floating Point Conversion
    struct AArch64EncFCONV
    {
        unsigned rd : 5 = 0b0;
        unsigned rn : 5 = 0b0;
        unsigned op1 : 6 = 0b0;
        unsigned opcode : 3 = 0b0;
        unsigned rmode : 2 = 0b0;
        unsigned _1 : 1 = 0b1;
        unsigned ptype : 2 = 0b0;
        unsigned op0 : 5 = 0b1111'0;
        unsigned s : 1 = 0b0;
        unsigned _0 : 1 = 0b0;
        unsigned sf : 1 = 0b1;
    };
    static_assert(sizeof(AArch64EncFCONV) == 4);

    /// Floating Point Data Processing (2 Sources)
    struct AArch64EncFDP2
    {
        unsigned rd : 5 = 0b0;
        unsigned rn : 5 = 0b0;
        unsigned _2 : 2 = 0b10;
        unsigned opcode : 4 = 0b0;
        unsigned rm : 5 = 0b0;
        unsigned _1 : 1 = 0b1;
        unsigned ptype : 2 = 0b0;
        unsigned op0 : 5 = 0b1111'0;
        unsigned s : 1 = 0b0;
        unsigned _0 : 1 = 0b0;
        unsigned m : 1 = 0b0;
    };
    static_assert(sizeof(AArch64EncFDP2) == 4);

    /// Unconditional Branch (Register)
    struct AArch64EncUBR
    {
        unsigned op4 : 5 = 0b0;
        unsigned rn : 5 = 0b0;
        unsigned op3 : 6 = 0b0;
        unsigned op2 : 5 = 0b0;
        unsigned opc : 4 = 0b0;
        unsigned op0 : 7 = 0b1101'011;
    };
    static_assert(sizeof(AArch64EncUBR) == 4);

    /// Conditional Branch (Immediate)
    struct AArch64EncCBI
    {
        unsigned cond : 4 = 0b0;
        unsigned o0 : 1 = 0b0;
        unsigned imm : 19 = 0b0;
        unsigned o1 : 1 = 0b0;
        unsigned op0 : 7 = 0b0101'010;
    };
    static_assert(sizeof(AArch64EncCBI) == 4);

    /// Load-Store Register (Unsigned Immediate)
    struct AArch64EncLSRUI
    {
        unsigned rt : 5 = 0b0;
        unsigned rm : 5 = 0b0;
        unsigned imm : 12 = 0b0;
        unsigned opc : 2 = 0b0;
        unsigned op1 : 2 = 0b01;
        unsigned v : 1 = 0b0;
        unsigned op0 : 3 = 0b111;
        unsigned size : 2 = 0b0;
    };
    static_assert(sizeof(AArch64EncLSRUI) == 4);

    /// Load-Store Register Pair (Offset)
    struct AArch64EncLSRPO
    {
        unsigned rt : 5 = 0b0;
        unsigned rn : 5 = 0b0;
        unsigned rt2 : 5 = 0b0;
        unsigned imm : 7 = 0b0;
        unsigned l : 1 = 0b0;
        unsigned op1 : 3 = 0b010;
        unsigned v : 1 = 0b0;
        unsigned op0 : 3 = 0b101;
        unsigned opc : 2 = 0b0;
    };
    static_assert(sizeof(AArch64EncLSRPO) == 4);

    using AArch64Encoding = std::variant<std::uint32_t, AArch64EncDPASI, AArch64EncDPASE, AArch64DPASS, AArch64EncDPMI, AArch64EncDPBI, AArch64EncDPPCR, AArch64EncDP2, AArch64EncDP3, AArch64EncDPL,
            AArch64EncFCONV, AArch64EncFDP2, AArch64EncUBR, AArch64EncCBI, AArch64EncLSRUI, AArch64EncLSRPO>;

    struct AArch64EncBinaryExtractor
    {
        template<typename T>
        std::uint32_t operator()(T const &value) const
        {
            return *reinterpret_cast<std::uint32_t const *>(&value);
        }
    };

    class AArch64Instruction : public NativeInstruction
    {
    protected:
        AArch64Encoding encoding_ = static_cast<std::uint32_t>(0);

    public:
        [[nodiscard]] std::size_t GetBinarySize() const noexcept override;
        std::size_t AppendToBuffer(std::vector<std::uint8_t> &buffer) override;
        void SetPCRelativeTarget(std::size_t pc) override;

        explicit AArch64Instruction(AArch64Encoding encoding) : encoding_(encoding) {}
    };
} // namespace city

#endif // CITY_AARCH64INSTRUCTION_H
