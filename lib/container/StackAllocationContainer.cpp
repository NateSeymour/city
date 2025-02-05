#include <city/container/StackAllocationContainer.h>

using namespace city;

void StackAllocationContainer::LoadIntoAmd64Register(Amd64RegisterLoader *loader, Amd64Register &target)
{
    loader->Load(target, *this);
}

void StackAllocationContainer::SetOffset(std::size_t offset)
{
    this->base_offset_ = offset;
}

std::size_t StackAllocationContainer::GetSize() const noexcept
{
    return this->size_;
}

std::size_t StackAllocationContainer::GetOffset() const noexcept
{
    return this->base_offset_;
}

StackAllocationContainer::StackAllocationContainer(std::size_t size) : size_(size) {}
