#ifndef CITY_CONSTANTVALUE_H
#define CITY_CONSTANTVALUE_H

#include <vector>
#include "Value.h"

namespace city
{
    class Builder;

    class ConstantValue : public Value
    {
        friend class Builder;

    protected:
        std::vector<std::byte> data_;

    public:
        [[nodiscard]] bool IsCompileTimeConstant() const noexcept override;

        ConstantValue(Type type, std::vector<std::byte> const &data);
    };
} // namespace city

#endif // CITY_CONSTANTVALUE_H
