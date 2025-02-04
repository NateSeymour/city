#include <city/runtime/NativeMemoryHandle.h>
#include <format>
#include <iostream>
#include <stdexcept>
#include <utility>

using namespace city;

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

std::size_t NativeMemoryHandle::GetAllocationSize() const noexcept
{
    return this->size_;
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

NativeMemoryHandle::NativeMemoryHandle(std::size_t size, void *address, MemoryProtection protection) : size_(size), address_(address), protection_(protection) {}

NativeMemoryHandle::NativeMemoryHandle(NativeMemoryHandle &&other) noexcept
{
    this->protection_ = std::exchange(other.protection_, static_cast<MemoryProtection>(0));
    this->size_ = std::exchange(other.size_, 0);
    this->address_ = std::exchange(other.address_, nullptr);
}
