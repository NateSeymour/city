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

std::vector<Value *> const &IRFunction::GetArgs() const noexcept
{
    return this->arg_values_;
}

IRFunction::IRFunction(std::string name, Type ret, std::vector<Value *> const &args) : name_(std::move(name)), ret_type_(ret), arg_values_(args)
{
    (void)this->AppendBlock();
}
