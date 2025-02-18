#include <city/backend/amd64/Amd64FunctionTranslator.h>
#include <city/backend/amd64/Amd64Module.h>
#include <city/backend/amd64/instruction/Amd64Instruction.h>

using namespace city;

/*
Object Amd64Module::Compile()
{
    std::vector<std::uint8_t> text;
    SymbolTable symtab;
    std::size_t offset = 0;
    for (auto &function : this->functions_)
    {
        symtab[function.name_] = {
                .location = reinterpret_cast<std::byte *>(offset),
                .flags = SymbolFlags::Executable,
        };

        for (auto &inst : function.prolog_)
        {
            offset += inst.AppendToBuffer(text);
        }

        for (auto &inst : function.text_)
        {
            if (inst.HasStub())
            {
                auto stub = inst.GetStub();
                stub.dst_offset = offset + inst.GetStubOffset();
                this->stubs_.push_back(stub);
            }

            offset += inst.AppendToBuffer(text);
        }
    }

    return {std::move(this->data_), std::move(text), std::move(symtab), std::move(this->stubs_)};
}
*/

Amd64Module::Amd64Module(std::string name, std::vector<std::uint8_t> data) : NativeModule(std::move(name), std::move(data)) {}
