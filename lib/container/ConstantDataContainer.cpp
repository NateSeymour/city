#include <city/container/ConstantDataContainer.h>

using namespace city;

std::vector<std::byte> const &ConstantDataContainer::GetData() const noexcept
{
    return this->data_;
}

void ConstantDataContainer::LoadIntoAmd64Register(Amd64RegisterLoader *loader, Amd64Register &target)
{
    loader->Load(target, this);
}

ConstantDataContainer::ConstantDataContainer(std::vector<std::byte> const &data) : data_(data) {}
