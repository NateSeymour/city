#include <city/Function.h>
#include <city/Value.h>

using namespace city;

Function *Value::ToFunction() noexcept
{
    return dynamic_cast<Function *>(this);
}

void Value::IncrementReadCount() noexcept
{
    this->read_count_++;
}

void Value::DecrementReadCount() noexcept
{
    this->read_count_--;
}

void Value::AssociateContainer(Container *container)
{
    this->container_ = container;
}

void Value::Disassociate()
{
    this->container_ = nullptr;
}

Container *Value::GetContainer() const noexcept
{
    return this->container_;
}

bool Value::IsInstantiated() const noexcept
{
    return this->container_;
}

bool Value::IsUsed() const noexcept
{
    return this->read_count_ > 0;
}

Type const &Value::GetType() const noexcept
{
    return this->type_;
}

std::size_t Value::GetReadCount() const noexcept
{
    return this->read_count_;
}

Value::Value(Type type) : type_(type) {}
