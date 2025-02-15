#include "city/value/ConstantValue.h"

using namespace city;

ConstantValue::ConstantValue(Type type, ConstantDataContainer container) : Value(type), data_container_(std::move(container))
{
    this->data_container_.InstantiateValue(this);
}
