#include "city/container/ConstantDataContainer.h"
#include <stdexcept>
#include "city/backend/IRTranslator.h"

using namespace city;

void ConstantDataContainer::Load(IRTranslator &translator, Register &dst)
{
    translator.Load(dst, *this);
}

void ConstantDataContainer::Store(IRTranslator &translator, Register &src)
{
    throw std::runtime_error("cannot store value into constant container");
}

std::size_t ConstantDataContainer::GetSize() const noexcept
{
    return this->data_.size();
}

ContainerType ConstantDataContainer::GetType() const noexcept
{
    return ContainerType::Constant;
}

std::vector<std::uint8_t> const &ConstantDataContainer::GetDataBuffer() const noexcept
{
    return this->data_;
}

ConstantDataContainer::ConstantDataContainer(std::vector<std::uint8_t> data) : data_(std::move(data)) {}
