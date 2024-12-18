#include "x86.h"
#include "ir/Block.h"
#include "ir/Function.h"
#include "ir/instruction/IRInstruction.h"
#include "x86TranslationInterface.h"

using namespace city;

Object x86::BuildModule(Module &module)
{
    Object object;

    x86TranslationInterface translator{object};
    for (auto &function : module.functions_)
    {
        for (auto block : function->blocks_)
        {
            for (auto &instruction : block->instructions_)
            {
                instruction->Apply(&translator);
            }
        }
    }
}

x86::x86()
{
    this->registers_ = {
            x86Register(x86RegisterCode::XMM0),
            x86Register(x86RegisterCode::XMM1),
            x86Register(x86RegisterCode::XMM2),
            x86Register(x86RegisterCode::XMM3),
            x86Register(x86RegisterCode::XMM4),
            x86Register(x86RegisterCode::XMM5),
            x86Register(x86RegisterCode::XMM6),
            x86Register(x86RegisterCode::XMM7),
    };
}
