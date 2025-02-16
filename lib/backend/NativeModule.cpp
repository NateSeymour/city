#include "city/backend/NativeModule.h"

using namespace city;

std::size_t NativeModule::AlignPC(std::size_t alignment)
{
    std::size_t misalignment = this->pc_ % alignment;
    this->pc_ += misalignment;

    return misalignment;
}

std::size_t NativeModule::GetBinarySize() const noexcept
{
    return this->cdata_.size() + (this->stubs_.size() * sizeof(void *)) + this->text_.size();
}

NativeModule::NativeModule(std::string name, std::vector<std::uint8_t> cdata) : name_(std::move(name)), cdata_(std::move(cdata)) {}
