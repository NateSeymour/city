#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include <array>
#include <cstdint>
#include <cstring>
#include <initializer_list>

namespace city
{
    template<std::size_t MaxSize>
    class ByteBuffer
    {
        std::size_t size_ = 0;
        std::array<std::uint8_t, MaxSize> buffer_;

    public:
        [[nodiscard]] std::size_t GetSize() const noexcept
        {
            return this->size_;
        }

        constexpr ByteBuffer(std::initializer_list<std::uint8_t> bytes)
        {
            this->size_ = std::min(bytes.size(), MaxSize);
            memcpy(this->buffer_.data(), bytes.begin(), this->size_);
        }

        constexpr ByteBuffer() = default;
    };
} // namespace city

#endif // BYTEBUFFER_H
