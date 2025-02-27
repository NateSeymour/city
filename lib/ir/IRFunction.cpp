#include <city/ir/IRFunction.h>

using namespace city;

IRBlock &IRFunction::GetFirstBlock() const noexcept
{
    return *this->first_block_;
}

IRBlock &IRFunction::GetLastBlock() const noexcept
{
    auto last_block = &this->GetFirstBlock();

    while (last_block->GetSuccessor() != nullptr)
    {
        last_block = last_block->GetSuccessor();
    }

    return *last_block;
}

std::vector<Value *> const &IRFunction::GetArgumentValues() const noexcept
{
    return this->arg_values_;
}

IRFunction::IRFunction(std::string name, Type return_type, std::vector<Type> argument_types, std::vector<Value *> argument_values) :
    Function(std::move(name), return_type, std::move(argument_types)), arg_values_(std::move(argument_values))
{
    this->first_block_ = std::make_unique<IRBlock>(*this);
}
