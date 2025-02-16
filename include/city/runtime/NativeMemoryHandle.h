#ifndef CITY_EXECUTABLEMEMORYHANDLE_H
#define CITY_EXECUTABLEMEMORYHANDLE_H

#include <cstddef>
#include <cstdint>

namespace city
{
    enum class MemoryProtection : std::uint8_t
    {
        Read = (1 << 0),
        Write = (1 << 1),
        Execute = (1 << 2),
    };

    constexpr MemoryProtection operator|(MemoryProtection a, MemoryProtection b)
    {
        return static_cast<MemoryProtection>(static_cast<std::uint8_t>(a) | static_cast<std::uint8_t>(b));
    }

    constexpr std::uint8_t operator&(MemoryProtection a, MemoryProtection b)
    {
        return static_cast<std::uint8_t>(a) & static_cast<std::uint8_t>(b);
    }

    class NativeMemoryHandle
    {
        MemoryProtection protection_;
        std::size_t size_;
        void *address_;

        NativeMemoryHandle(std::size_t size, void *address, MemoryProtection protection);

    public:
        void DebugDump() const;

        void SetProtection(MemoryProtection protection);

        [[nodiscard]] void *GetAddressAtOffset(std::size_t offset) const;

        [[nodiscard]] std::size_t GetAllocationSize() const noexcept;

        [[nodiscard]] bool IsReadable() const noexcept;
        [[nodiscard]] bool IsWritable() const noexcept;
        [[nodiscard]] bool IsExecutable() const noexcept;

        [[nodiscard]] static NativeMemoryHandle Allocate(std::size_t size);

        NativeMemoryHandle() = delete;
        NativeMemoryHandle(NativeMemoryHandle const &) = delete;
        NativeMemoryHandle(NativeMemoryHandle &&other) noexcept;
        ~NativeMemoryHandle();
    };
} // namespace city

#endif // CITY_EXECUTABLEMEMORYHANDLE_H
