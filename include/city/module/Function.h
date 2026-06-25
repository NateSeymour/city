#ifndef CITY_FUNCTION_H
#define CITY_FUNCTION_H

#include <utility>
#include <vector>
#include "Type.h"
#include "Block.h"

namespace city
{
    class IRBuilder;

    template <typename ArchitectureT>
    class Function
    {
    protected:
        Type return_type_;
        std::vector<Type> argument_types_;
        Block<ArchitectureT> main_block_;

    public:
        [[nodiscard]] Type const &GetReturnType() const noexcept
        {
            return this->return_type_;
        }

        [[nodiscard]] std::vector<Type> const &GetArgumentTypes() const noexcept
        {
            return this->argument_types_;
        }

        Function(Type return_type, std::vector<Type> argument_types) : return_type_(return_type), argument_types_(std::move(argument_types)) {}
    };
} // namespace city

#endif // CITY_FUNCTION_H
