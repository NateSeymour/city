#include "Value.h"

using namespace city;

void Value::IncrementReadCount() noexcept
{
    this->read_count_++;
}

void Value::IncrementWriteCount() noexcept
{
    this->write_count_++;
}

bool Value::IsConstant() const noexcept
{
    return this->write_count_ == 0;
}

bool Value::IsUsed() const noexcept
{
    return this->read_count_ > 0;
}

bool Value::IsCompileTimeConstant() const noexcept
{
    return false;
}

Type Value::GetType() const noexcept
{
    return this->type_;
}

Value::Value(Type type, StorageClass storage_class) : type_(type), storage_class_(storage_class) {}
