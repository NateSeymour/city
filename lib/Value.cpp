#include <city/Function.h>
#include <city/Value.h>

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

void Value::IncrementReadCount() noexcept
{
    this->read_count_++;
}

void Value::DecrementReadCount() noexcept
{
    this->read_count_--;
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
