#ifndef CITY_BACKEND_H
#define CITY_BACKEND_H

#include "ir/Module.h"
#include "ir/Object.h"

namespace city
{
    class Backend
    {
    public:
        [[nodiscard]] virtual Object BuildModule(Module &module) = 0;

        /**
         * Instantiates and returns a handle to the host-native compiler backend.
         * @return Host Native Backend
         */
        [[nodiscard]] static std::unique_ptr<Backend> CreateHostNative();

        virtual ~Backend() = default;
    };
} // namespace city

#endif // CITY_BACKEND_H
