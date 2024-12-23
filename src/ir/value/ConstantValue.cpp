#include "ConstantValue.h"

using namespace city;

bool ConstantValue::IsCompileTimeConstant() const noexcept
{
    return true;
}

ConstantValue::ConstantValue(Type type, std::vector<std::byte> const &data) : Value(type, StorageClass::Constant), data_(data) {}
