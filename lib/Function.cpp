#include <city/Function.h>

using namespace city;

std::string const &Function::GetName() const noexcept
{
    return this->name_;
}

std::vector<Type> const &Function::GetArgumentTypes() const noexcept
{
    return this->argument_types_;
}

Function::Function(std::string name, Type return_type, std::vector<Type> arg_types) : Value(return_type), name_(std::move(name)), argument_types_(std::move(arg_types)) {}
