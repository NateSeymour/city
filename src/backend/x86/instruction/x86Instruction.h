#ifndef X86_64INSTRUCTION_H
#define X86_64INSTRUCTION_H

#include <array>
#include <cstdint>
#include "ByteBuffer.h"
#include "ir/instruction/Instruction.h"

namespace city
{
    /**
     * Container to hold the x86 maximum opcode size (3 bytes).
     */
    using x86Opcode = ByteBuffer<3>;

    /**
     * Container to hold the x86 maximum immediate size (8 bytes == 1QW).
     */
    using x86Immediate = ByteBuffer<8>;

    class x86Instruction : public Instruction
    {
    public:
        x86Opcode opcode = {};
        std::uint8_t mod_rm = 0x0;
        std::uint8_t sib = 0x0;
        x86Immediate immediate = {};
    };
} // namespace city

#endif // X86_64INSTRUCTION_H
