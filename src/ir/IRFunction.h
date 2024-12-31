#ifndef CITY_IRFUNCTION_H
#define CITY_IRFUNCTION_H

#include <list>
#include <memory>
#include <value/Value.h>
#include "block/IRBlock.h"
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

        std::list<IRBlock> blocks_;

        std::vector<std::unique_ptr<Value>> local_values_;

    public:
        [[nodiscard]] IRBlock &GetFirstBlock() noexcept;
        [[nodiscard]] IRBlock &GetLastBlock() noexcept;

        [[nodiscard]] IRBlock &AppendBlock();

        IRFunction(Type ret, std::vector<Type> const &args);
    };
} // namespace city

#endif // CITY_IRFUNCTION_H
