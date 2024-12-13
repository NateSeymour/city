#ifndef CITY_EXECUTABLEMEMORYHANDLE_H
#define CITY_EXECUTABLEMEMORYHANDLE_H

#include <cstddef>
#include <cstdint>

namespace city
{
    enum class MemoryProtection : std::uint8_t
    {
        Read = (1<<0),
        Write = (1<<1),
        Execute = (1<<2),
    };

    inline MemoryProtection operator|(MemoryProtection a, MemoryProtection b)
    {
        return static_cast<MemoryProtection>(static_cast<std::uint8_t>(a) | static_cast<std::uint8_t>(b));
    }

    inline std::uint8_t operator&(MemoryProtection a, MemoryProtection b)
    {
        return static_cast<std::uint8_t>(a) & static_cast<std::uint8_t>(b);
    }

    class ExecutableMemoryHandle
    {
        MemoryProtection protection_;
        std::size_t size_;
        void *address_;

        ExecutableMemoryHandle(std::size_t size, void *address, MemoryProtection protection);

    public:
        [[nodiscard]] static ExecutableMemoryHandle Allocate(std::size_t size);

        [[nodiscard]] void *GetAddressAtOffset(std::size_t offset) const;
        void SetProtection(MemoryProtection protection);

        [[nodiscard]] bool IsReadable() const noexcept;
        [[nodiscard]] bool IsWritable() const noexcept;
        [[nodiscard]] bool IsExecutable() const noexcept;

        ExecutableMemoryHandle() = delete;
        ExecutableMemoryHandle(ExecutableMemoryHandle const &) = delete;
        ~ExecutableMemoryHandle();
    };
} // city

#endif //CITY_EXECUTABLEMEMORYHANDLE_H
