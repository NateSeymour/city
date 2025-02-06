#include <city/backend/amd64/Amd64FunctionTranslator.h>
#include <city/container/ConstantDataContainer.h>

using namespace city;

void ConstantDataContainer::Load(Amd64FunctionTranslator &translator, Amd64Register &dst)
{
    translator.Load(dst, *this);
}

void ConstantDataContainer::Store(Amd64FunctionTranslator &translator, Amd64Register &src)
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

ConstantDataContainer::ConstantDataContainer(std::size_t size, std::size_t offset) : size_(size), offset_(offset) {}
