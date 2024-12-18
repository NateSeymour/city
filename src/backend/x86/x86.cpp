#include "x86.h"
#include "instruction/memory/Amd64MovMR64.h"
#include "instruction/memory/Amd64PopO64.h"
#include "instruction/memory/Amd64PushO64.h"
#include "ir/Block.h"
#include "ir/Function.h"
#include "ir/instruction/IRInstruction.h"
#include "x86TranslationInterface.h"

using namespace city;

std::array<x86Register, 8> const x86_register_definitions = {
        x86Register(x86RegisterCode::XMM0),
        x86Register(x86RegisterCode::XMM1),
        x86Register(x86RegisterCode::XMM2),
        x86Register(x86RegisterCode::XMM3),
        x86Register(x86RegisterCode::XMM4),
        x86Register(x86RegisterCode::XMM5),
        x86Register(x86RegisterCode::XMM6),
        x86Register(x86RegisterCode::XMM7),
};

Object x86::BuildModule(Module &module)
{
    Object object;

    x86TranslationInterface translator{object};
    for (auto &function : module.functions_)
    {
        // Function Prolog
        object.EmplaceInstruction<Amd64PushO64>(x86RegisterCode::RBP);
        object.EmplaceInstruction<Amd64MovMR64>(x86RegisterCode::RBP, x86RegisterCode::RSP);

        // Function Body
        for (auto block : function->blocks_)
        {
            for (auto &instruction : block->instructions_)
            {
                instruction->Apply(&translator);
            }
        }
    }

    return std::move(object);
}

x86::x86() : registers_(x86_register_definitions) {}
