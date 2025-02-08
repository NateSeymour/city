#ifndef CITY_FUNCTION_H
#define CITY_FUNCTION_H

#include <string>
#include <vector>
#include "type/Type.h"

namespace city
{
    class IRBuilder;

    class Function
    {
        friend class IRBuilder;

    protected:
        std::string name_;
        Type return_type_;
        std::vector<Type> arg_types_;

    public:
        [[nodiscard]] std::string const &GetName() const noexcept;

        Function(std::string name, Type return_type, std::vector<Type> arg_types);
    };
} // namespace city

#endif // CITY_FUNCTION_H
