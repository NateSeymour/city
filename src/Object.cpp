#include "Object.h"

using namespace city;

void Object::RegisterSymbol(std::string const &name, NativeInstruction *entry)
{
    this->symbol_table_[name] = entry;
}

std::size_t Object::GetBinarySize() const noexcept
{
    std::size_t size = 0;

    for (auto &instruction : this->instructions_)
    {
        size += instruction->GetBinarySize();
    }

    return size;
}

std::size_t Object::WriteToBuffer(std::byte *buffer) const
{
    std::byte *buffer_it = buffer;
    for (auto &instruction : this->instructions_)
    {
        buffer_it += instruction->WriteToBuffer(buffer_it);
    }

    return buffer_it - buffer;
}
