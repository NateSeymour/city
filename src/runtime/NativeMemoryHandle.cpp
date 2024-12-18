#include "NativeMemoryHandle.h"
#include <format>
#include <iostream>
#include <stdexcept>

using namespace city;

NativeMemoryHandle::NativeMemoryHandle(std::size_t size, void *address, MemoryProtection protection) : size_(size), address_(address), protection_(protection) {}

void NativeMemoryHandle::DebugDump() const
{
    std::cout << std::format("Memory Debug Dump @{}", this->address_);

    for (std::size_t i = 0; i < this->size_; i++)
    {
        if (i % 10 == 0)
        {
            std::cout << "\n";
        }

        std::cout << std::format("{:02X}.", ((std::uint8_t *)this->address_)[i]);
    }

    std::cout << "\nEnd Debug Dump" << std::endl;
}

std::byte *NativeMemoryHandle::GetAddressAtOffset(std::size_t offset) const
{
    if (offset > this->size_)
    {
        throw std::runtime_error("offset is too large");
    }

    return static_cast<std::byte *>(this->address_) + offset;
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
