#include <city/Function.h>

using namespace city;

std::string const &Function::GetName() const noexcept
{
    return this->name_;
}

Function::Function(std::string name, Type return_type, std::vector<Type> arg_types) : name_(std::move(name)), return_type_(return_type), arg_types_(std::move(arg_types)) {}
