#ifndef CITY_FUNCTION_H
#define CITY_FUNCTION_H

#include <string_view>
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
        std::string name_;

        Type return_type_;
        std::vector<Type> argument_types_;

        Block<ArchitectureT> main_block_;
        std::reference_wrapper<Block<ArchitectureT>> insertion_block_ = std::ref(main_block_);

    public:
        [[nodiscard]] std::string const &GetName() const noexcept
        {
            return this->name_;
        }

        [[nodiscard]] Type const &GetReturnType() const noexcept
        {
            return this->return_type_;
        }

        [[nodiscard]] std::vector<Type> const &GetArgumentTypes() const noexcept
        {
            return this->argument_types_;
        }

        [[nodiscard]] Block<ArchitectureT> &GetInsertionBlock() noexcept
        {
            return this->insertion_block_;
        }

        Function(std::string_view name, Type const return_type, std::vector<Type> argument_types) : name_(name), return_type_(return_type), argument_types_(std::move(argument_types)) {}

        Function(Function &&) = delete;
        Function(Function &) = delete;
    };
} // namespace city

#endif // CITY_FUNCTION_H
