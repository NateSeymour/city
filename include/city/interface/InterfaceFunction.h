#ifndef CITY_INTERFACEFUNCTION_H
#define CITY_INTERFACEFUNCTION_H

#include <city/Function.h>

namespace city
{
    class JIT;

    class InterfaceFunction : public Function
    {
        friend class JIT;
        
    protected:
        void *address_;

    public:
        InterfaceFunction(std::string name, Type return_type, std::vector<Type> arg_types, void *address);
    };
} // namespace city

#endif // CITY_INTERFACEFUNCTION_H
