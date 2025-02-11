#ifndef NATIVEMODULE_H
#define NATIVEMODULE_H

#include <string>
#include <vector>
#include "city/Object.h"
#include "city/Symbol.h"

namespace city
{
    class NativeModule
    {
    protected:
        std::string name_;
        std::vector<std::uint8_t> data_;
        StubList stubs_;

    public:
        [[nodiscard]] virtual Object Compile() = 0;

        NativeModule(std::string name, std::vector<std::uint8_t> data);
        virtual ~NativeModule() = default;
    };
} // namespace city

#endif // NATIVEMODULE_H
