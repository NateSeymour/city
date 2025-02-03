#include <city/backend/amd64/Amd64FunctionTranslator.h>
#include <city/backend/amd64/Amd64Module.h>
#include <city/backend/amd64/instruction/Amd64Instruction.h>
#include <city/backend/amd64/instruction/memory/Amd64Mov.h>
#include <city/backend/amd64/instruction/memory/Amd64Push.h>

using namespace city;

Object Amd64Module::Compile()
{
    std::vector<std::uint8_t> text;
    std::size_t offset = 0;
    for (auto &inst : this->instructions_)
    {
        if (inst.HasLabel())
        {
            this->symtab_[inst.GetLabel()] = {
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

Amd64Module::Amd64Module(std::string name) : name_(std::move(name)) {}
