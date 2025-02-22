#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include <array>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <vector>

namespace city
{
    template<std::size_t MaxSize>
    class ByteBuffer
    {
        std::size_t size_ = 0;
        std::array<std::uint8_t, MaxSize> buffer_;

    public:
        [[nodiscard]] std::uint8_t const *GetBuffer() const noexcept
        {
            return static_cast<std::uint8_t const *>(this->buffer_.data());
        }

        [[nodiscard]] std::size_t GetSize() const noexcept
        {
            return this->size_;
        }

        std::uint8_t *begin()
        {
            return this->buffer_.data();
        }

        std::uint8_t *end()
        {
            return this->buffer_.data() + this->size_;
        }

        constexpr ByteBuffer(std::uint8_t value)
        {
            this->size_ = std::min(static_cast<std::size_t>(1), MaxSize);
            memcpy(this->buffer_.data(), reinterpret_cast<void *>(&value), 1);
        }

        constexpr ByteBuffer(std::uint16_t value)
        {
            this->size_ = std::min(static_cast<std::size_t>(2), MaxSize);
            memcpy(this->buffer_.data(), reinterpret_cast<void *>(&value), 2);
        }

        constexpr ByteBuffer(std::uint32_t value)
        {
            this->size_ = std::min(static_cast<std::size_t>(4), MaxSize);
            memcpy(this->buffer_.data(), reinterpret_cast<void *>(&value), 4);
        }

        constexpr ByteBuffer(std::uint64_t value)
        {
            this->size_ = std::min(static_cast<std::size_t>(8), MaxSize);
            memcpy(this->buffer_.data(), reinterpret_cast<void *>(&value), 8);
        }

        constexpr ByteBuffer(std::int8_t value)
        {
            this->size_ = std::min(static_cast<std::size_t>(1), MaxSize);
            memcpy(this->buffer_.data(), reinterpret_cast<void *>(&value), 1);
        }

        constexpr ByteBuffer(std::int16_t value)
        {
            this->size_ = std::min(static_cast<std::size_t>(2), MaxSize);
            memcpy(this->buffer_.data(), reinterpret_cast<void *>(&value), 2);
        }

        constexpr ByteBuffer(std::int32_t value)
        {
            this->size_ = std::min(static_cast<std::size_t>(4), MaxSize);
            memcpy(this->buffer_.data(), reinterpret_cast<void *>(&value), 4);
        }

        constexpr ByteBuffer(std::int64_t value)
        {
            this->size_ = std::min(static_cast<std::size_t>(8), MaxSize);
            memcpy(this->buffer_.data(), reinterpret_cast<void *>(&value), 8);
        }

        constexpr ByteBuffer(std::initializer_list<std::uint8_t> bytes)
        {
            this->size_ = std::min(bytes.size(), MaxSize);
            memcpy(this->buffer_.data(), bytes.begin(), this->size_);
        }

        ByteBuffer(std::vector<std::uint8_t> const &bytes)
        {
            this->size_ = std::min(bytes.size(), MaxSize);
            memcpy(this->buffer_.data(), bytes.data(), this->size_);
        }

        ByteBuffer(std::array<std::uint8_t, MaxSize> const &bytes)
        {
            this->size_ = std::min(bytes.size(), MaxSize);
            memcpy(this->buffer_.data(), bytes.data(), this->size_);
        }

        constexpr ByteBuffer() = default;
    };
} // namespace city

#endif // BYTEBUFFER_H
