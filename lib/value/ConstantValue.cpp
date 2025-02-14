#include "city/value/ConstantValue.h"

using namespace city;

Container *ConstantValue::GetContainer() noexcept
{
    return &this->data_container_;
}

void ConstantValue::IncrementReadCount() noexcept
{
    /* Do Nothing */
}

void ConstantValue::DecrementReadCount() noexcept
{
    /* Do Nothing */
}

std::size_t ConstantValue::GetReadCount() const noexcept
{
    return 1;
}

bool ConstantValue::IsInstantiated() const noexcept
{
    return true;
}

bool ConstantValue::IsUsed() const noexcept
{
    return true;
}

bool ConstantValue::Release()
{
    return Value::Release();
}

ConstantValue::ConstantValue(Type type, ConstantDataContainer container) : Value(type), data_container_(std::move(container)) {}
