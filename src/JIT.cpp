#include "JIT.h"
#include "runtime/NativeMemoryHandle.h"

using namespace city;

void JIT::AddModule(std::unique_ptr<Module> module)
{
    this->modules_.push_back(std::move(module));
}

void JIT::RemoveModule(std::string const &name) {}

Assembly JIT::CompileModules()
{
    // Build modules
    for (auto &module : this->modules_)
    {
        auto object = this->backend_->BuildModule(*module);
        this->objects_.push_back(std::move(object));
    }

    this->modules_.clear();

    // Generate Assembly
    std::size_t assembly_size = 0;
    for (auto &object : this->objects_)
    {
        assembly_size += object.GetBinarySize();
    }
    auto memory_handle = NativeMemoryHandle::Allocate(assembly_size);

    std::size_t offset = 0;
    for (auto &object : this->objects_)
    {
        offset += object.WriteToBuffer(memory_handle.GetAddressAtOffset(offset));
    }

    memory_handle.SetProtection(MemoryProtection::Read | MemoryProtection::Execute);

    Assembly assembly(std::move(memory_handle));

    /* Populate symbol table */

    return assembly;
}

JIT::JIT()
{
    this->backend_ = Backend::CreateHostNative();
}