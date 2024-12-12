#ifndef CITY_VALUE_H
#define CITY_VALUE_H

#include <cstddef>

namespace city
{
    class Value
    {
        std::size_t read_count_ = 0;
        std::size_t write_count_ = 0;
    };
} // city

#endif //CITY_VALUE_H
