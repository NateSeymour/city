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
        ConstantValue(Type type, std::vector<std::byte> const &data);
    };
} // city

#endif //CITY_CONSTANTVALUE_H
