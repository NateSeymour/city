#ifndef CITY_VALUE_H
#define CITY_VALUE_H

#include <cstddef>
#include "ir/type/Type.h"

namespace city
{
    class Value
    {
        Type type_;

        std::size_t read_count_ = 0;
        std::size_t write_count_ = 0;

    public:
        Value(Type type);
    };
} // city

#endif //CITY_VALUE_H
