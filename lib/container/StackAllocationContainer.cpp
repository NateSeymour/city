#include <city/container/StackAllocationContainer.h>

using namespace city;

void StackAllocationContainer::LoadIntoAmd64Register(Amd64RegisterLoader *loader, Amd64Register &target)
{
    loader->Load(target, *this);
}

StackAllocationContainer::StackAllocationContainer(std::size_t size) : size_(size) {}
