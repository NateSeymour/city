#ifdef __APPLE__
#include <city/runtime/MacOS.h>
#include <city/runtime/NativeMemoryHandle.h>
#include <stdexcept>
#include <sys/mman.h>

using namespace city;

NativeMemoryHandle NativeMemoryHandle::Allocate(std::size_t size)
{
    auto protection = MemoryProtection::Read | MemoryProtection::Write;

    void *addr = mmap(nullptr, size, memory_protection_to_native(protection), MAP_PRIVATE | MAP_ANON | MAP_JIT, -1, 0);

    if (addr == MAP_FAILED)
    {
        throw std::runtime_error("failed to allocated exectuable memory");
    }

    return {size, addr, protection};
}

void NativeMemoryHandle::SetProtection(MemoryProtection protection)
{
    if (mprotect(this->address_, this->size_, memory_protection_to_native(protection)) != 0)
    {
        throw std::runtime_error("failed to set memory protection");
    }

    this->protection_ = protection;
}

NativeMemoryHandle::~NativeMemoryHandle()
{
    munmap(this->address_, this->size_);
}

int city::memory_protection_to_native(MemoryProtection protection)
{
    int native_protection = 0;

    native_protection |= protection & MemoryProtection::Read ? PROT_READ : 0;
    native_protection |= protection & MemoryProtection::Write ? PROT_WRITE : 0;
    native_protection |= protection & MemoryProtection::Execute ? PROT_EXEC : 0;

    return native_protection;
}
#endif
