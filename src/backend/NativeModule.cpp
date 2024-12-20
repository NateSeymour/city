#include "NativeModule.h"

using namespace city;

std::size_t NativeModule::GetBinarySize() const noexcept
{
    std::size_t size = 0;

    for (auto &instruction : this->instructions_)
    {
        size += instruction->GetBinarySize();
    }

    return size;
}

std::size_t NativeModule::WriteToBuffer(std::byte *buffer) const
{
    std::byte *buffer_it = buffer;
    for (auto &instruction : this->instructions_)
    {
        buffer_it += instruction->WriteToBuffer(buffer_it);
    }

    return buffer_it - buffer;
}
