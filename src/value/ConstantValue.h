#ifndef CITY_CONSTANTVALUE_H
#define CITY_CONSTANTVALUE_H

#include <vector>
#include "value/Value.h"

namespace city
{
    class ConstantValue : public Value
    {
        std::vector<std::byte> data_;

    public:
        [[nodiscard]] bool IsCompileTimeConstant() const noexcept override;
        [[nodiscard]] std::vector<std::byte> const &GetDataBuffer() const override;

        ConstantValue(Type type, std::vector<std::byte> data);
    };
} // namespace city

#endif // CITY_CONSTANTVALUE_H
