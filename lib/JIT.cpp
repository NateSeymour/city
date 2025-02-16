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
    this->modules_.insert({module.GetName(), this->backend_->BuildIRModule(std::move(module))});
}

void JIT::RemoveModule(std::string const &name)
{
    this->interfaces_.erase(name);
    this->modules_.erase(name);
}

Assembly JIT::Link() const
{
    // Create memory allocations
    std::size_t assembly_text_size = 0;
    for (auto const &[name, object] : this->modules_)
    {
        assembly_text_size += object.GetBinarySize();
    }

    if (assembly_text_size == 0)
    {
        throw std::runtime_error("cannot link empty modules");
    }

    Assembly assembly{NativeMemoryHandle::Allocate(assembly_text_size)};

    // Process Interfaces
    for (auto const &[name, interface] : this->interfaces_)
    {
        for (auto const &function : interface.functions_)
        {
            assembly.symtab_.try_emplace(name, *function, function->address_);
        }
    }

    // Process Modules
    std::size_t module_offset = 0;
    std::vector<std::pair<std::string, void **>> stubs;
    for (auto const &[name, module] : this->modules_)
    {
        auto insertion_addr = assembly.text_.GetAddressAtOffset(module_offset);

        memcpy(insertion_addr, module.cdata_.data(), module.cdata_.size());

        insertion_addr += module.cdata_.size();
        insertion_addr += module.stubs_.size() * sizeof(void *);

        for (int i = 0; i < module.stubs_.size(); i++)
        {
            stubs.emplace_back(module.stubs_[i], static_cast<void **>(insertion_addr - ((i + 1) * sizeof(void *))));
        }

        memcpy(insertion_addr, module.text_.data(), module.text_.size());

        for (auto &[symbol_name, symbol] : module.symtab_)
        {
            assembly.symtab_.try_emplace(symbol_name, symbol, insertion_addr + reinterpret_cast<std::size_t>(symbol.GetLocation()));
        }

        module_offset += module.GetBinarySize();
    }

    // Perform linking
    for (auto &[name, addr] : stubs)
    {
        *addr = assembly.symtab_[name].GetLocation();
    }

    assembly.text_.SetProtection(MemoryProtection::Read | MemoryProtection::Execute);

    return assembly;
}

JIT::JIT()
{
    this->backend_ = Backend::CreateHostNative();
}
