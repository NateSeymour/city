#ifndef CITY_TYPE_H
#define CITY_TYPE_H

#include <cstddef>

namespace city
{
    class IRBuilder;

    enum class NativeType
    {
        Void,
        Integer,
        FloatingPoint,
    };

    class Type
    {
        friend class IRBuilder;

    protected:
        std::size_t size_ = 0;
        NativeType native_type_ = NativeType::Integer;

    public:
        [[nodiscard]] NativeType GetNativeType() const noexcept
        {
            return this->native_type_;
        }

        bool operator==(Type const &rhs) const noexcept
        {
            return this->size_ == rhs.size_ && this->native_type_ == rhs.native_type_;
        }

        [[nodiscard]] bool IsVoid() const noexcept
        {
            return this->native_type_ == NativeType::Void;
        }
    };
} // namespace city

#endif // CITY_TYPE_H
