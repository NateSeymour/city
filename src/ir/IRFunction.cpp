#include "IRFunction.h"

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

IRFunction::IRFunction(Type ret, std::vector<Type> const &args) : ret_type_(ret), arg_types_(args)
{
    (void)this->AppendBlock();
}
