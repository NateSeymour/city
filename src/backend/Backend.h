#ifndef CITY_BACKEND_H
#define CITY_BACKEND_H

#include <cstddef>
#include "ir/Module.h"
#include "ir/Object.h"

namespace city
{
    class Backend
    {
        std::size_t pointer_size_;

    public:
        [[nodiscard]] virtual Object BuildModule(Module &module) const = 0;
    };
} // city

#endif //CITY_BACKEND_H
