#include "city/value/Value.h"
#include "city/Function.h"

using namespace city;

bool Value::Release()
{
    if (this->container_ == nullptr || !this->IsUsed())
    {
        this->container_ = nullptr;
        return true;
    }

    return false;
}

Function *Value::ToFunction() noexcept
{
    return dynamic_cast<Function *>(this);
}

std::optional<std::string> const &Value::GetName() const noexcept
{
    return this->name_;
}

void Value::IncrementReadCount() noexcept
{
    this->read_count_++;
}

void Value::DecrementReadCount() noexcept
{
    this->read_count_--;
}

Container *Value::GetContainer() noexcept
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

Value::Value(std::string name, Type type) : name_(std::move(name)), type_(type) {}
