#include <city/ir/IRFunction.h>

using namespace city;

std::string const &IRFunction::GetName() const noexcept
{
    return this->name_;
}

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

void IRFunction::SetArgs(std::vector<Value *> const &args)
{
    this->arg_values_ = args;
}

std::vector<Value *> const &IRFunction::GetArgs() const noexcept
{
    return this->arg_values_;
}

IRFunction::IRFunction(std::string name, Type return_value, std::vector<Type> arg_types) : Function(std::move(name), return_value, std::move(arg_types))
{
    (void)this->AppendBlock();
}
