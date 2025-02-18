#include "city/container/StubContainer.h"
#include "city/backend/IRTranslator.h"

using namespace city;

std::size_t StubContainer::GetSize() const noexcept
{
    return sizeof(void *);
}

ContainerType StubContainer::GetType() const noexcept
{
    return ContainerType::Constant;
}

void StubContainer::Load(IRTranslator &translator, Register &dst)
{
    translator.Load(dst, *this);
}

void StubContainer::Store(IRTranslator &translator, Register &src)
{
    throw std::runtime_error("stub containers are constant and cannot be stored into");
}
