#ifndef CITY_IRFUNCTION_H
#define CITY_IRFUNCTION_H

#include <city/Function.h>
#include <city/Value.h>
#include <city/type/Type.h>
#include <list>
#include <memory>
#include <ranges>
#include <string>
#include "block/IRBlock.h"

namespace city
{
    class IRBuilder;
    struct Amd64FunctionTranslator;

    class IRFunction : public Function
    {
        friend class IRBuilder;
        friend struct Amd64FunctionTranslator;

    protected:
        std::vector<Value *> arg_values_;
        std::list<IRBlock> blocks_;

    public:
        [[nodiscard]] IRBlock &GetFirstBlock() noexcept;
        [[nodiscard]] IRBlock &GetLastBlock() noexcept;
        [[nodiscard]] std::vector<Value *> const &GetArgumentValues() const noexcept;

        [[nodiscard]] IRBlock &AppendBlock();

        IRFunction(std::string name, Type return_type, std::vector<Type> argument_types, std::vector<Value *> argument_values);
    };
} // namespace city

#endif // CITY_IRFUNCTION_H
