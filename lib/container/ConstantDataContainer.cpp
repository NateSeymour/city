#include <city/container/ConstantDataContainer.h>

using namespace city;

void ConstantDataContainer::LoadIntoAmd64Register(Amd64RegisterLoader *loader, Amd64Register &target)
{
    loader->Load(target, *this);
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
