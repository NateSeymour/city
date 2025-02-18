#include <city/Function.h>

using namespace city;

std::vector<Type> const &Function::GetArgumentTypes() const noexcept
{
    return this->argument_types_;
}

Function::Function(std::string name, Type return_type, std::vector<Type> arg_types) :
    Value(std::move(name), Type::Get<long>()), return_type_(return_type), argument_types_(std::move(arg_types))
{
    this->stub_container_.InstantiateValue(this);
}
