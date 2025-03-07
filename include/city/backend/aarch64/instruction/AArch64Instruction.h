#ifndef CITY_AARCH64INSTRUCTION_H
#define CITY_AARCH64INSTRUCTION_H

#include <cstdint>

#include "city/backend/NativeInstruction.h"

namespace city
{
    union AArch64Encoding
    {
        struct DPAddSubI
        {
            unsigned rd : 5 = 0b0;
            unsigned rn : 5 = 0b0;
            unsigned imm : 12 = 0b0;
            unsigned sh : 1 = 0b0;
            unsigned op0 : 6 = 0b1000'10;
            unsigned s : 1 = 0b0;
            unsigned op : 1 = 0b0;
            unsigned sf : 1 = 0b1;
        } dp_add_sub_i;
        static_assert(sizeof(DPAddSubI) == 4);

        struct DPMovI
        {
            unsigned rd : 5 = 0b0;
            unsigned imm : 16 = 0b0;
            unsigned hw : 2 = 0b0;
            unsigned op0 : 6 = 0b1001'01;
            unsigned opc : 2 = 0b0;
            unsigned sf : 1 = 0b1;
        } dpmi;
        static_assert(sizeof(DPMovI) == 4);

        /// Data Processing Bitfield (Immediate)
        struct DPBI
        {
            unsigned rd : 5 = 0b0;
            unsigned rn : 5 = 0b0;
            unsigned imms : 6 = 0b0;
            unsigned immr : 6 = 0b0;
            unsigned n : 1 = 0b0;
            unsigned op0 : 6 = 0b1001'10;
            unsigned opc : 2 = 0b0;
            unsigned sf : 1 = 0b1;
        } dpbi;
        static_assert(sizeof(DPBI) == 4);

        struct DPAddSubExt
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
        } dp_add_sub_ext;
        static_assert(sizeof(DPAddSubExt) == 4);

        struct DPAddSubShift
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
        } dp_add_sub_shift;
        static_assert(sizeof(DPAddSubShift) == 4);

        struct DPPCR
        {
            unsigned rd : 5 = 0b0;
            unsigned immhi : 19 = 0b0;
            unsigned op0 : 5 = 0b1000'0;
            unsigned immlo : 2 = 0b0;
            unsigned op : 1 = 0b0;
        } dppcr;
        static_assert(sizeof(DPPCR) == 4);

        struct DP2
        {
            unsigned rd : 5 = 0b0;
            unsigned rn : 5 = 0b0;
            unsigned opcode : 6 = 0b0;
            unsigned rm : 5 = 0b0;
            unsigned op0 : 8 = 0b1101'0110;
            unsigned s : 1 = 0b0;
            unsigned _0 : 1 = 0b0;
            unsigned sf : 1 = 0b1;
        } dp2;
        static_assert(sizeof(DP2) == 4);

        struct DP3
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
        } dp3;
        static_assert(sizeof(DP3) == 4);

        struct DPL
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
        } dpl;
        static_assert(sizeof(DPL) == 4);

        struct FCONV
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
        } fconv;
        static_assert(sizeof(FCONV) == 4);

        struct FDP2
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
        } fdp2;
        static_assert(sizeof(FDP2) == 4);

        /// Unconditional Branch (Register)
        struct UBR
        {
            unsigned op4 : 5 = 0b0;
            unsigned rn : 5 = 0b0;
            unsigned op3 : 6 = 0b0;
            unsigned op2 : 5 = 0b0;
            unsigned opc : 4 = 0b0;
            unsigned op0 : 7 = 0b1101'011;
        } ubr;
        static_assert(sizeof(UBR) == 4);

        /// Conditional Branch (Immediate)
        struct CBI
        {
            unsigned cond : 4 = 0b0;
            unsigned o0 : 1 = 0b0;
            unsigned imm : 19 = 0b0;
            unsigned o1 : 1 = 0b0;
            unsigned op0 : 7 = 0b0101'010;
        } cbi;
        static_assert(sizeof(CBI) == 4);

        /// Load-Store Register (Unsigned Immediate)
        struct LSRUI
        {
            unsigned rt : 5 = 0b0;
            unsigned rm : 5 = 0b0;
            unsigned imm : 12 = 0b0;
            unsigned opc : 2 = 0b0;
            unsigned op1 : 2 = 0b01;
            unsigned v : 1 = 0b0;
            unsigned op0 : 3 = 0b111;
            unsigned size : 2 = 0b0;
        } lsrui;
        static_assert(sizeof(LSRUI) == 4);

        /// Load-Store Register Pair (Offset)
        struct LSRPO
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
        } lsrpo;
        static_assert(sizeof(LSRPO) == 4);

        std::uint32_t raw = 0;

        [[nodiscard]] operator std::uint32_t() const
        {
            return this->raw;
        }
    };

    class AArch64Instruction : public NativeInstruction
    {
        std::uint32_t encoding_ = 0;

    public:
        [[nodiscard]] std::size_t GetBinarySize() const noexcept override;
        std::size_t AppendToBuffer(std::vector<std::uint8_t> &buffer) override;

        AArch64Instruction(std::uint32_t encoding) : encoding_(encoding) {}
    };
} // namespace city

#endif // CITY_AARCH64INSTRUCTION_H
