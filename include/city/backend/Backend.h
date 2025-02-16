#ifndef CITY_BACKEND_H
#define CITY_BACKEND_H

#include "NativeModule.h"
#include "city/ir/IRModule.h"

namespace city
{
    class Backend
    {
    public:
        [[nodiscard]] virtual NativeModule BuildIRModule(IRModule &&ir_module) = 0;

        /**
         * Instantiates and returns a handle to the host-native compiler backend.
         * @return Host Native Backend
         */
        [[nodiscard]] static std::unique_ptr<Backend> CreateHostNative();

        virtual ~Backend() = default;
    };
} // namespace city

#endif // CITY_BACKEND_H
