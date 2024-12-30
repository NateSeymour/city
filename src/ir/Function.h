#ifndef CITY_FUNCTION_H
#define CITY_FUNCTION_H

#include "Block.h"
#include "type/Type.h"

namespace city
{
    class IRBuilder;
    class AArch64;
    class Amd64;

    class Function
    {
        friend class IRBuilder;
        friend class AArch64;
        friend class Amd64;

    protected:
        Type ret_type_;
        std::vector<Type> arg_types_;

        Block *first_block_;
        std::vector<Block *> blocks_;

    public:
        Function(Type ret, std::vector<Type> const &args, Block *first_block);
    };
} // namespace city

#endif // CITY_FUNCTION_H
