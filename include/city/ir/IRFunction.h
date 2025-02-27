#ifndef CITY_IRFUNCTION_H
#define CITY_IRFUNCTION_H

#include <list>
#include <string>
#include "block/IRBlock.h"
#include "city/Function.h"
#include "city/type/Type.h"
#include "city/value/Value.h"

namespace city
{
    class IRBuilder;
    class AArch64FunctionTranslator;
    class Amd64FunctionTranslator;

    class IRFunction : public Function
    {
        friend class IRBuilder;

    protected:
        std::vector<Value *> arg_values_;
        std::unique_ptr<IRBlock> first_block_;

    public:
        [[nodiscard]] std::vector<Value *> const &GetArgumentValues() const noexcept;

        [[nodiscard]] IRBlock &GetFirstBlock() const noexcept;
        [[nodiscard]] IRBlock &GetLastBlock() const noexcept;

        IRFunction(std::string name, Type return_type, std::vector<Type> argument_types, std::vector<Value *> argument_values);
    };
} // namespace city

#endif // CITY_IRFUNCTION_H
