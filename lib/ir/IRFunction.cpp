#include <city/ir/IRFunction.h>

using namespace city;

IRBlock &IRFunction::GetFirstBlock() noexcept
{
    return this->blocks_.front();
}

IRBlock &IRFunction::GetLastBlock() noexcept
{
    return this->blocks_.back();
}

IRBlock &IRFunction::AppendBlock()
{
    return this->blocks_.emplace_back(*this);
}

std::vector<Value *> const &IRFunction::GetArgumentValues() const noexcept
{
    return this->arg_values_;
}

IRFunction::IRFunction(std::string name, Type return_type, std::vector<Type> argument_types, std::vector<Value *> argument_values) :
    Function(std::move(name), return_type, std::move(argument_types)), arg_values_(std::move(argument_values))
{
    (void)this->AppendBlock();
}
