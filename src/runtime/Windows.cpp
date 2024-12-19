#ifdef WIN64

#include "Windows.h"
#include <stdexcept>
#include <windows.h>
#include "NativeMemoryHandle.h"

using namespace city;

NativeMemoryHandle NativeMemoryHandle::Allocate(std::size_t size)
{
    auto protection = MemoryProtection::Read | MemoryProtection::Write;

    void *addr = VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, memory_protection_to_native(protection));

    if (addr == nullptr)
    {
        throw std::runtime_error("failed to allocated exectuable memory");
    }

    return {size, addr, protection};
}

void NativeMemoryHandle::SetProtection(MemoryProtection protection)
{
    DWORD old_protection;
    if (!VirtualProtect(this->address_, this->size_, memory_protection_to_native(protection), &old_protection))
    {
        throw std::runtime_error("failed to set memory protection");
    }

    this->protection_ = protection;
}

NativeMemoryHandle::~NativeMemoryHandle()
{
    VirtualFree(this->address_, 0, MEM_RELEASE);
}

DWORD city::memory_protection_to_native(MemoryProtection protection)
{
    switch (protection)
    {
        case MemoryProtection::Read:
        {
            return PAGE_READONLY;
        }

        case MemoryProtection::Execute:
        {
            return PAGE_EXECUTE;
        }

        case MemoryProtection::Read | MemoryProtection::Execute:
        {
            return PAGE_EXECUTE_READ;
        }

        case MemoryProtection::Read | MemoryProtection::Write:
        {
            return PAGE_READWRITE;
        }

        default:
        {
            return PAGE_NOACCESS;
        }
    }
}

#endif
