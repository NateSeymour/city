#ifndef CITY_FUNCTION_H
#define CITY_FUNCTION_H

#include <vector>
#include "city/value/Value.h"
#include "container/StubContainer.h"
#include "type/Type.h"

namespace city
{
    class IRBuilder;

    class Function : public Value
    {
        friend class IRBuilder;

        StubContainer stub_container_;

    protected:
        Type return_type_;
        std::vector<Type> argument_types_;

    public:
        [[nodiscard]] std::vector<Type> const &GetArgumentTypes() const noexcept;

        Function(std::string name, Type return_type, std::vector<Type> arg_types);
    };
} // namespace city

#endif // CITY_FUNCTION_H
