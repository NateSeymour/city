#include "ExecutableMemoryHandle.h"
#include <stdexcept>

using namespace city;

ExecutableMemoryHandle::ExecutableMemoryHandle(std::size_t size, void *address, MemoryProtection protection)
    : size_(size), address_(address), protection_(protection) {}

void *ExecutableMemoryHandle::GetAddressAtOffset(std::size_t offset) const
{
    if(offset > this->size_)
    {
        throw std::runtime_error("offset is too large");
    }

    return static_cast<char*>(this->address_) + offset;
}

bool ExecutableMemoryHandle::IsReadable() const noexcept
{
    return this->protection_ & MemoryProtection::Read;
}

bool ExecutableMemoryHandle::IsWritable() const noexcept
{
    return this->protection_ & MemoryProtection::Write;
}

bool ExecutableMemoryHandle::IsExecutable() const noexcept
{
    return this->protection_ & MemoryProtection::Execute;
}
