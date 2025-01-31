#include <city/backend/amd64/Amd64Module.h>
#include <city/backend/amd64/Amd64Translator.h>
#include <city/backend/amd64/instruction/Amd64Instruction.h>
#include <city/backend/amd64/instruction/memory/Amd64Mov.h>
#include <city/backend/amd64/instruction/memory/Amd64Push.h>

using namespace city;

void Amd64Module::TranslateIRFunctions()
{
    Amd64Translator translator{*this};
    for (auto &[name, function] : this->ir_module_.functions_)
    {
        // Function Prolog
        auto entry = Amd64Push::O64(Amd64RegisterCode::RBP);
        entry.SetLabel(name);
        this->Insert(std::move(entry));

        this->Insert(Amd64Mov::MR64(Amd64RegisterCode::RBP, Amd64RegisterCode::RSP));

        // Function Body
        for (auto &block : function->blocks_)
        {
            for (auto &instruction : block.instructions_)
            {
                instruction->Apply(&translator);
            }
        }
    }
}

void Amd64Module::Insert(Amd64Instruction &&instruction)
{
    this->instructions_.push_back(instruction);
}

Object Amd64Module::Compile()
{
    std::vector<std::uint8_t> text;
    std::size_t offset = 0;
    for (auto &inst : this->instructions_)
    {
        if (inst.HasLabel())
        {
            auto &label = inst.GetLabel();

            this->symtab_[label] = {
                    .location = reinterpret_cast<std::byte *>(offset),
                    .flags = SymbolFlags::Executable,
            };
        }

        if (inst.HasStub())
        {
            auto stub = inst.GetStub();
            stub.dst_offset = offset + inst.GetStubOffset();
            this->stubs_.push_back(stub);
        }

        offset += inst.AppendToBuffer(text);
    }

    return {std::move(this->data_), std::move(text), std::move(this->symtab_), std::move(this->stubs_)};
}

Amd64Module::Amd64Module(IRModule &ir_module) : ir_module_(ir_module)
{
    this->data_ = std::move(ir_module.data_);

    this->TranslateIRFunctions();
}
