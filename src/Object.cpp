#include "Object.h"

using namespace city;

std::size_t Object::GetBinarySize() const noexcept
{
    return this->native_memory_.GetAllocationSize();
}

Object::Object(NativeMemoryHandle &&native_memory, SymbolTable &&symbol_table) : native_memory_(std::move(native_memory)), symbol_table_(std::move(symbol_table)) {}
