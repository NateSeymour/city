#ifndef CITY_IRFUNCTION_H
#define CITY_IRFUNCTION_H

#include <list>
#include <memory>
#include "../Value.h"
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
        std::string name_;
        Type ret_type_;
        std::vector<Type> arg_types_;

        std::list<IRBlock> blocks_;

        std::vector<std::unique_ptr<Value>> local_values_;

    public:
        [[nodiscard]] std::string const &GetName() const noexcept;
        [[nodiscard]] IRBlock &GetFirstBlock() noexcept;
        [[nodiscard]] IRBlock &GetLastBlock() noexcept;

        [[nodiscard]] IRBlock &AppendBlock();

        IRFunction(std::string name, Type ret, std::vector<Type> const &args);
    };
} // namespace city

#endif // CITY_IRFUNCTION_H
