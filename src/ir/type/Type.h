#ifndef CITY_TYPE_H
#define CITY_TYPE_H

#include <cstddef>

namespace city
{
    class Builder;

    enum class NativeType
    {
        Void,
        Integer,
        FloatingPoint,
    };

    class Type
    {
        friend class Builder;

    protected:
        std::size_t size_ = 0;
        NativeType native_type_ = NativeType::Integer;

    public:
        bool operator==(Type const &rhs) const noexcept
        {
            return this->size_ == rhs.size_ && this->native_type_ == rhs.native_type_;
        }
    };
} // city

#endif //CITY_TYPE_H