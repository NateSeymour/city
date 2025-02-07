#ifndef CITY_TYPE_H
#define CITY_TYPE_H

#include <concepts>
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
        template<typename T>
        [[nodiscard]] static Type Get()
        {
            Type type;

            if constexpr (std::is_integral_v<T>)
            {
                type.size_ = sizeof(T);
                type.native_type_ = NativeType::Integer;
            }
            else if constexpr (std::is_floating_point_v<T>)
            {
                type.size_ = sizeof(T);
                type.native_type_ = NativeType::FloatingPoint;
            }
            else if constexpr (std::is_same_v<T, void>)
            {
                type.size_ = 0;
                type.native_type_ = NativeType::Void;
            }
            else
            {
                static_assert("Unrecognized Native Type!");
            }

            return type;
        }

        [[nodiscard]] std::size_t GetSize() const noexcept
        {
            return this->size_;
        }

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
