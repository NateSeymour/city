#include "JIT.h"
#include "runtime/NativeMemoryHandle.h"

using namespace city;

void JIT::CompileIRModules()
{
    for (auto &[name, module] : this->ir_modules_)
    {
        this->objects_.insert({name, this->backend_->BuildModule(module)});
    }

    this->ir_modules_.clear();
}

Assembly JIT::LinkObjects() const
{
    std::size_t allocation_size = 0;
    for (auto const &[name, object] : this->objects_)
    {
        allocation_size += object.GetBinarySize();
    }
    auto native_memory = NativeMemoryHandle::Allocate(allocation_size);

    Assembly assembly{std::move(native_memory)};

    std::size_t object_insertion_offset = 0;
    for (auto const &[name, object] : this->objects_)
    {
        auto object_size = object.GetBinarySize();

        auto assembly_addr = assembly.native_memory_.GetAddressAtOffset(object_insertion_offset);
        auto object_addr = object.native_memory_.GetAddressAtOffset(0);
        memcpy(assembly_addr, object_addr, object_size);

        object_insertion_offset += object_size;

        for (auto &[name, offset] : object.symbol_table_)
        {
            assembly.symbol_table_[name] = {
                    .location = assembly_addr + reinterpret_cast<std::size_t>(offset.location),
                    .flags = SymbolFlags::Exectuable,
            };
        }
    }

    assembly.native_memory_.SetProtection(MemoryProtection::Read | MemoryProtection::Execute);

    return assembly;
}

void JIT::InsertIRModule(IRModule module)
{
    this->ir_modules_.insert({module.GetName(), std::move(module)});
}

void JIT::RemoveModule(std::string const &name)
{
    this->ir_modules_.erase(name);
    this->objects_.erase(name);
}

Assembly JIT::CompileAndLink()
{
    this->CompileIRModules();

    return this->LinkObjects();
}

JIT::JIT()
{
    this->backend_ = Backend::CreateHostNative();
}
