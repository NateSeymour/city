#include "Object.h"

using namespace city;

std::size_t Object::GetBinarySize() const noexcept
{
    return this->native_memory_.GetAllocationSize();
}

Object Object::FromNativeModule(NativeModule const &module)
{
    // Allocate memory
    std::size_t allocation_size = 0;
    for (auto &inst : module.instructions_)
    {
        allocation_size += inst->GetBinarySize();
    }
    auto native_memory = NativeMemoryHandle::Allocate(allocation_size);

    // Create object
    Object object{std::move(native_memory)};

    // Write to buffer
    std::size_t offset = 0;
    for (auto &inst : module.instructions_)
    {
        auto label = inst->GetLabel();
        if (label != nullptr)
        {
            object.symtab_[label] = offset;
        }

        auto addr = object.native_memory_.GetAddressAtOffset(offset);
        offset += inst->WriteToBuffer(addr);
    }

    return object;
}

Object::Object(NativeMemoryHandle native_memory) : native_memory_(std::move(native_memory)) {}
