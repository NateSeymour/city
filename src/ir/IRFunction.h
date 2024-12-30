#ifndef CITY_IRFUNCTION_H
#define CITY_IRFUNCTION_H

#include "IRBlock.h"
#include "type/Type.h"

namespace city
{
    class IRBuilder;
    class AArch64;
    class Amd64;

    class IRFunction
    {
        friend class IRBuilder;
        friend class AArch64;
        friend class Amd64;

    protected:
        Type ret_type_;
        std::vector<Type> arg_types_;

        IRBlock *first_block_;
        std::vector<IRBlock *> blocks_;

    public:
        IRFunction(Type ret, std::vector<Type> const &args, IRBlock *first_block);
    };
} // namespace city

#endif // CITY_IRFUNCTION_H
