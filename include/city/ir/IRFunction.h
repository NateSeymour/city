#ifndef CITY_IRFUNCTION_H
#define CITY_IRFUNCTION_H

#include <city/Function.h>
#include <city/Value.h>
#include <city/type/Type.h>
#include <list>
#include <memory>
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

        std::vector<std::unique_ptr<Value>> local_values_;

        void SetArgs(std::vector<Value *> const &args);

    public:
        [[nodiscard]] std::string const &GetName() const noexcept;
        [[nodiscard]] IRBlock &GetFirstBlock() noexcept;
        [[nodiscard]] IRBlock &GetLastBlock() noexcept;
        [[nodiscard]] std::vector<Value *> const &GetArgs() const noexcept;

        [[nodiscard]] IRBlock &AppendBlock();

        IRFunction(std::string name, Type return_type, std::vector<Type> arg_types);
    };
} // namespace city

#endif // CITY_IRFUNCTION_H
