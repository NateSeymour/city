#include <city/JIT.h>
#include <city/interface/InterfaceFunction.h>
#include <city/runtime/NativeMemoryHandle.h>
#include <stdexcept>

using namespace city;

void JIT::InsertInterfaceModule(InterfaceModule &&module)
{
    this->interfaces_.insert({module.GetName(), std::move(module)});
}

void JIT::InsertIRModule(IRModule &&module)
{
    this->objects_.insert({module.GetName(), this->backend_->BuildIRModule(std::move(module))});
}

void JIT::RemoveModule(std::string const &name)
{
    this->interfaces_.erase(name);
    this->objects_.erase(name);
}

Assembly JIT::Link() const
{
    // Create memory allocations
    std::size_t assembly_data_size = 0;
    std::size_t assembly_text_size = 0;
    for (auto const &[name, object] : this->objects_)
    {
        assembly_data_size += object.GetDataSize();
        assembly_text_size += object.GetBinarySize();
    }
    auto data = NativeMemoryHandle::Allocate(assembly_data_size);
    auto text = NativeMemoryHandle::Allocate(assembly_text_size);

    Assembly assembly{std::move(data), std::move(text)};

    // Process Interfaces
    for (auto const &[name, interface] : this->interfaces_)
    {
        for (auto const &function : interface.functions_)
        {
            assembly.symtab_[function->name_] = {
                    .location = reinterpret_cast<std::byte *>(function->address_),
                    .flags = SymbolFlags::Executable,
            };
        }
    }

    // Process Objects
    StubList stubs;
    std::size_t data_offset = 0;
    std::size_t text_offset = 0;
    for (auto const &[name, object] : this->objects_)
    {
        auto data_size = object.GetDataSize();
        auto text_size = object.GetBinarySize();

        auto data_insertion_addr = assembly.data_.GetAddressAtOffset(data_offset);
        auto text_insertion_addr = assembly.text_.GetAddressAtOffset(text_offset);

        memcpy(data_insertion_addr, object.data_.data(), data_size);
        memcpy(text_insertion_addr, object.text_.data(), text_size);

        for (auto &[symbol_name, symbol] : object.symtab_)
        {
            assembly.symtab_[symbol_name] = {
                    .location = text_insertion_addr + reinterpret_cast<std::size_t>(symbol.location),
                    .flags = SymbolFlags::Executable,
            };
        }

        for (auto stub : object.stubs_)
        {
            switch (stub.type)
            {
                case StubSourceLocation::Data:
                {
                    stub.src_offset += data_offset;
                    break;
                }

                case StubSourceLocation::Text:
                {
                    stub.src_offset += text_offset;
                    break;
                }
            }

            stub.dst_offset += text_offset;
            stubs.push_back(std::move(stub));
        }

        data_offset += data_size;
        text_offset += text_size;
    }

    for (auto &stub : stubs)
    {
        auto ref_addr = reinterpret_cast<std::uint64_t *>(assembly.text_.GetAddressAtOffset(stub.dst_offset));

        if (*ref_addr != kLinkerCanary64)
        {
            throw std::runtime_error("failed to link symbol");
        }

        if (stub.label.has_value())
        {
            *ref_addr = reinterpret_cast<std::uint64_t>(assembly.symtab_[*stub.label].location);
        }
        else
        {
            switch (stub.type)
            {
                case StubSourceLocation::Data:
                {
                    *ref_addr = reinterpret_cast<std::uint64_t>(assembly.data_.GetAddressAtOffset(stub.src_offset));
                    break;
                }

                case StubSourceLocation::Text:
                {
                    *ref_addr = reinterpret_cast<std::uint64_t>(assembly.text_.GetAddressAtOffset(stub.src_offset));
                    break;
                }
            }
        }
    }

    assembly.data_.SetProtection(MemoryProtection::Read | MemoryProtection::Write);
    assembly.text_.SetProtection(MemoryProtection::Read | MemoryProtection::Execute);

    return assembly;
}

JIT::JIT()
{
    this->backend_ = Backend::CreateHostNative();
}
