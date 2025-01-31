#include <city/Object.h>

using namespace city;

std::size_t Object::GetDataSize() const noexcept
{
    return this->data_.size();
}

std::size_t Object::GetBinarySize() const noexcept
{
    return this->text_.size();
}

Object::Object(std::vector<std::uint8_t> data, std::vector<std::uint8_t> text, SymbolTable symtab, StubList stubs) :
    data_(std::move(data)), text_(std::move(text)), symtab_(std::move(symtab)), stubs_(std::move(stubs))
{
}
