#include "Value.h"

using namespace city;

Type Value::GetType() const noexcept
{
    return this->type_;
}

Value::Value(Type type, StorageClass storage_class) : type_(type), storage_class_(storage_class) {}
