#ifndef CITY_AMD64MODULE_H
#define CITY_AMD64MODULE_H

#include <vector>
#include "city/backend/NativeModule.h"

namespace city
{
    class Amd64;

    class Amd64Module : public NativeModule
    {
        friend class Amd64;

    protected:
        std::vector<Amd64Function> functions_;

    public:
        Amd64Module(std::string name, std::vector<std::uint8_t> data);
    };
} // namespace city

#endif // CITY_AMD64MODULE_H
