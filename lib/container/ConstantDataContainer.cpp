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

std::size_t ConstantDataContainer::GetOffset() const noexcept
{
    return this->offset_;
}

std::size_t ConstantDataContainer::GetSize() const noexcept
{
    return this->size_;
}

ContainerType ConstantDataContainer::GetType() const noexcept
{
    return ContainerType::Constant;
}

ConstantDataContainer::ConstantDataContainer(std::size_t size, std::size_t offset) : size_(size), offset_(offset) {}
