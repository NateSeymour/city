#include "Amd64.h"
#include "Amd64Translator.h"
#include "instruction/memory/Amd64Mov.h"
#include "instruction/memory/Amd64Push.h"
#include "ir/IRFunction.h"
#include "ir/block/IRBlock.h"
#include "ir/instruction/IRInstruction.h"

using namespace city;

std::array<Amd64Register, 8> const city::amd64_register_definitions = {
        Amd64Register(Amd64RegisterCode::XMM0),
        Amd64Register(Amd64RegisterCode::XMM1),
        Amd64Register(Amd64RegisterCode::XMM2),
        Amd64Register(Amd64RegisterCode::XMM3),
        Amd64Register(Amd64RegisterCode::XMM4),
        Amd64Register(Amd64RegisterCode::XMM5),
        Amd64Register(Amd64RegisterCode::XMM6),
        Amd64Register(Amd64RegisterCode::XMM7),
};

Object Amd64::BuildModule(IRModule &ir_module)
{
    Amd64Module amd64_module{};

    Amd64Translator translator{amd64_module};
    for (auto &[name, function] : ir_module.functions_)
    {
        // Function Prolog
        auto entry = Amd64Push::O64(Amd64RegisterCode::RBP);
        entry.SetLabel(name);
        amd64_module.Insert(std::move(entry));

        amd64_module.Insert(Amd64Mov::MR64(Amd64RegisterCode::RBP, Amd64RegisterCode::RSP));

        // Function Body
        for (auto &block : function->blocks_)
        {
            for (auto &instruction : block.instructions_)
            {
                instruction->Apply(&translator);
            }
        }
    }

    /* build module */
    // Allocate memory
    std::size_t allocation_size = 0;
    for (auto &inst : amd64_module.instructions_)
    {
        allocation_size += inst.GetBinarySize();
    }
    auto native_memory = NativeMemoryHandle::Allocate(allocation_size);

    // Symbol table
    SymbolTable symbol_table;

    // Write to buffer
    std::size_t offset = 0;
    for (auto &inst : amd64_module.instructions_)
    {
        auto label = inst.GetLabel();
        if (label != nullptr)
        {
            symbol_table[label] = {
                    .flags = SymbolFlags::Exectuable,
                    .location = reinterpret_cast<std::byte *>(offset),
            };
        }

        auto addr = native_memory.GetAddressAtOffset(offset);
        offset += inst.WriteToBuffer(addr);
    }

    return {std::move(native_memory), std::move(symbol_table)};
}
