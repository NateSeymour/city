#include "ConstantValue.h"

using namespace city;

bool ConstantValue::IsCompileTimeConstant() const noexcept
{
    return true;
}

std::vector<std::byte> const &ConstantValue::GetDataBuffer() const
{
    return this->data_;
}

ConstantValue::ConstantValue(Type type, std::vector<std::byte> data) : Value(type, StorageClass::Constant), data_(std::move(data)) {}
