#ifndef X86ADDRM32INST_H
#define X86ADDRM32INST_H

#include "backend/amd64/instruction/Amd64Instruction.h"
#include "ir/value/Value.h"

namespace city
{
    /**
     * ADD r32, r/m32
     */
    class Amd64AddRM32Inst : public Amd64Instruction
    {
    public:
        Amd64AddRM32Inst(Value *dst, Value *src)
        {
            this->SetOpcode({0x03});
        }
    };
} // namespace city

#endif // X86ADDRM32INST_H
