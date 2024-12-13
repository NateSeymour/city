#include "ConstantValue.h"

using namespace city;

ConstantValue::ConstantValue(Type type, std::vector<std::byte> const &data) : Value(type, StorageClass::Constant), data_(data) {}
