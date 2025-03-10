#include <city/Function.h>

using namespace city;

Type const &Function::GetReturnType() const noexcept
{
    return this->return_type_;
}

std::vector<Type> const &Function::GetArgumentTypes() const noexcept
{
    return this->argument_types_;
}

Function::Function(std::string name, Type return_type, std::vector<Type> arg_types) :
    Value(std::move(name), Type::Get<void *>()), return_type_(return_type), argument_types_(std::move(arg_types))
{
    this->stub_container_.InstantiateValue(this);
}
