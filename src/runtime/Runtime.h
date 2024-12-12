#ifndef CITY_RUNTIME_H
#define CITY_RUNTIME_H

#include <cstddef>

namespace city
{
    void *map_exectuable(std::size_t size);
    void unmap_executable(void *addr, std::size_t size);
} // city

#endif //CITY_RUNTIME_H
