#ifndef CITY_FUNCTION_H
#define CITY_FUNCTION_H

#include "Block.h"
#include "type/Type.h"

namespace city
{
    class Builder;

    class Function
    {
        friend class Builder;

    protected:
        std::string name_;
        Type ret_type_;
        std::vector<Type> arg_types_;
        Block *body_;

    public:
        Function(std::string name, Type ret, std::vector<Type> const &args, Block *body);
    };
} // city

#endif //CITY_FUNCTION_H
