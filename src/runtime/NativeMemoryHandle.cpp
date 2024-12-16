#include "NativeMemoryHandle.h"
#include <stdexcept>

using namespace city;

NativeMemoryHandle::NativeMemoryHandle(std::size_t size, void *address, MemoryProtection protection)
    : size_(size), address_(address), protection_(protection) {}

void *NativeMemoryHandle::GetAddressAtOffset(std::size_t offset) const
{
    if(offset > this->size_)
    {
        throw std::runtime_error("offset is too large");
    }

    return static_cast<char*>(this->address_) + offset;
}

bool NativeMemoryHandle::IsReadable() const noexcept
{
    return this->protection_ & MemoryProtection::Read;
}

bool NativeMemoryHandle::IsWritable() const noexcept
{
    return this->protection_ & MemoryProtection::Write;
}

bool NativeMemoryHandle::IsExecutable() const noexcept
{
    return this->protection_ & MemoryProtection::Execute;
}
