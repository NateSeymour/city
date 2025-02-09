#ifndef CITY_FUNCTION_H
#define CITY_FUNCTION_H

#include <city/Value.h>
#include <string>
#include <vector>
#include "type/Type.h"

namespace city
{
    class IRBuilder;

    class Function : public Value
    {
        friend class IRBuilder;

    protected:
        std::string name_;
        std::vector<Type> argument_types_;

    public:
        [[nodiscard]] std::string const &GetName() const noexcept;
        [[nodiscard]] std::vector<Type> const &GetArgumentTypes() const noexcept;

        Function(std::string name, Type return_type, std::vector<Type> arg_types);
    };
} // namespace city

#endif // CITY_FUNCTION_H
