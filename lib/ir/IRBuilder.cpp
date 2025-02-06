#include <city/container/StackAllocationContainer.h>
#include <city/ir/IRBuilder.h>
#include <city/ir/IRModule.h>

using namespace city;

ConstantDataContainer *IRBuilder::CreateConstantDataContainer(std::size_t size, std::size_t offset)
{
    auto &container = this->module_.global_constants_.emplace_back(std::make_unique<ConstantDataContainer>(size, offset));
    return container.get();
}

Value *IRBuilder::ReserveLocalValue(Type type)
{
    auto &function = this->insert_point_->parent_function_;
    auto &locals = function.local_values_;
    auto &value = locals.emplace_back(std::make_unique<Value>(type));

    return value.get();
}

IRBuilder::IRBuilder(IRModule &module) : module_(module) {}

IRBlock &IRBuilder::CreateBlock()
{
    auto &insert_function = this->insert_point_->parent_function_;
    return insert_function.AppendBlock();
}

IRFunction *IRBuilder::CreateFunction(std::string const &name)
{
    return this->CreateFunction(name, Type::Get<void>(), {});
}

IRFunction *IRBuilder::CreateFunction(std::string const &name, Type ret)
{
    return this->CreateFunction(name, ret, {});
}

IRFunction *IRBuilder::CreateFunction(std::string const &name, Type ret, std::vector<Type> const &args)
{
    auto [it, _] = this->module_.functions_.insert({name, std::make_unique<IRFunction>(name, ret, args)});
    auto function = it->second.get();

    this->SetInsertPoint(function->GetLastBlock());

    return function;
}

void IRBuilder::SetInsertPoint(IRBlock &block) noexcept
{
    this->insert_point_ = &block;
}

void IRBuilder::SetInsertPoint(IRFunction *function) noexcept
{
    this->SetInsertPoint(function->GetLastBlock());
}

IRBlock &IRBuilder::GetInsertPoint() const
{
    return *this->insert_point_;
}

IRFunction *IRBuilder::GetInsertFunction() const
{
    return &this->insert_point_->parent_function_;
}

Value *IRBuilder::CreateConstant(Type type, std::vector<std::uint8_t> const &data)
{
    // Append the constant data to the module
    std::size_t offset = this->module_.data_.size();
    this->module_.data_.insert(this->module_.data_.end(), data.begin(), data.end());

    auto container = this->CreateConstantDataContainer(data.size(), offset);
    auto value = this->ReserveLocalValue(type);

    value->AssociateContainer(container);
    container->AssociateValue(value);

    return value;
}

Value *IRBuilder::InsertCallInst(IRFunction *function)
{
    auto retval = this->ReserveLocalValue(function->ret_type_);
    (void)this->ReserveInstruction<CallInst>(retval, function);

    return retval;
}

Value *IRBuilder::InsertRetInst(Value *retval)
{
    if (!retval)
    {
        retval = this->ReserveLocalValue(Type::Get<void>());
    }

    (void)this->ReserveInstruction<RetInst>(retval);

    return retval;
}
