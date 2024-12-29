#include "Amd64.h"
#include "Amd64Translator.h"
#include "instruction/memory/Amd64MovMR64.h"
#include "instruction/memory/Amd64PopO64.h"
#include "instruction/memory/Amd64PushO64.h"
#include "ir/Block.h"
#include "ir/Function.h"
#include "ir/instruction/IRInstruction.h"

using namespace city;

std::array<Amd64Register, 8> const x86_register_definitions = {
        Amd64Register(Amd64RegisterCode::XMM0),
        Amd64Register(Amd64RegisterCode::XMM1),
        Amd64Register(Amd64RegisterCode::XMM2),
        Amd64Register(Amd64RegisterCode::XMM3),
        Amd64Register(Amd64RegisterCode::XMM4),
        Amd64Register(Amd64RegisterCode::XMM5),
        Amd64Register(Amd64RegisterCode::XMM6),
        Amd64Register(Amd64RegisterCode::XMM7),
};

NativeModule Amd64::BuildModule(IRModule &module)
{
    NativeModule object{};

    Amd64Translator translator{object};
    for (auto &function : module.functions_)
    {
        // Function Prolog
        auto entry = object.EmplaceInstruction<Amd64PushO64>(Amd64RegisterCode::RBP);
        entry->SetLabel(function->name_);

        object.EmplaceInstruction<Amd64MovMR64>(Amd64RegisterCode::RBP, Amd64RegisterCode::RSP);

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
