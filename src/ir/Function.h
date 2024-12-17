#ifndef CITY_FUNCTION_H
#define CITY_FUNCTION_H

#include "Block.h"
#include "type/Type.h"

namespace city
{
    class Builder;
    class AArch64;
    class x86;

    class Function
    {
        friend class Builder;
        friend class AArch64;
        friend class x86;

    protected:
        std::string name_;
        Type ret_type_;
        std::vector<Type> arg_types_;

        Block *first_block_;
        std::vector<Block *> blocks_;

    public:
        Function(std::string name, Type ret, std::vector<Type> const &args, Block *first_block);
    };
} // namespace city

#endif // CITY_FUNCTION_H
