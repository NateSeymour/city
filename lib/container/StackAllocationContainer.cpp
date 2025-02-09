#include <city/backend/amd64/Amd64FunctionTranslator.h>
#include <city/container/StackAllocationContainer.h>

using namespace city;

void StackAllocationContainer::Load(Amd64FunctionTranslator &translator, Amd64Register &dst)
{
    translator.Load(dst, *this);
}

void StackAllocationContainer::Store(Amd64FunctionTranslator &translator, Amd64Register &src)
{
    translator.Store(*this, src);
}

void StackAllocationContainer::SetOffset(std::int64_t offset)
{
    this->base_offset_ = offset;
}

std::size_t StackAllocationContainer::GetSize() const noexcept
{
    return this->size_;
}

std::int64_t StackAllocationContainer::GetOffset() const noexcept
{
    return this->base_offset_;
}

ContainerType StackAllocationContainer::GetType() const noexcept
{
    return ContainerType::StackAllocation;
}

StackAllocationContainer::StackAllocationContainer(std::size_t size) : size_(size) {}
