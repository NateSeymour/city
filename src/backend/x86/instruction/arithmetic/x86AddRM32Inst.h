#ifndef X86ADDRM32INST_H
#define X86ADDRM32INST_H

#include "backend/x86/instruction/x86Instruction.h"
#include "ir/value/Value.h"

namespace city
{
    /**
     * ADD r32, r/m32
     */
    class x86AddRM32Inst : public x86Instruction
    {
    public:
        x86AddRM32Inst(Value *dst, Value *src)
        {
            this->opcode = {0x03};
        }
    };
} // namespace city

#endif // X86ADDRM32INST_H
