#include "Builder.h"
#include "Module.h"

using namespace city;

Builder::Builder(Module &module) : module_(module) {}

Block *Builder::CreateBlock()
{
    auto &block = this->module_.blocks_.emplace_back();
    return block.get();
}

Function *Builder::CreateFunction(std::string name)
{
    return this->CreateFunction(std::move(name), this->GetBuiltinType<void>(), {});
}

Function *Builder::CreateFunction(std::string name, Type ret)
{
    return this->CreateFunction(std::move(name), ret, {});
}

Function *Builder::CreateFunction(std::string name, Type ret, std::vector<Type> const &args)
{
    auto block = this->CreateBlock();
    auto &function = this->module_.functions_.emplace_back(std::make_unique<Function>(std::move(name), ret, args, block));

    return function.get();
}

void Builder::SetInsertPoint(Block *block) noexcept
{
    this->insert_point_ = block;
}

void Builder::SetInsertPoint(Function *function) noexcept
{
    this->SetInsertPoint(function->body_);
}

Block *Builder::GetInsertPoint() const noexcept
{
    return this->insert_point_;
}

ConstantValue *Builder::CreateConstant(Type type, const std::vector<std::byte> &data)
{
    auto value = std::make_unique<ConstantValue>(type, data);
    auto ret = value.get();

    this->module_.global_values_.push_back(std::move(value));

    return ret;
}
