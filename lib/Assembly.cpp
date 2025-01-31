#include <city/Assembly.h>

using namespace city;

Symbol Assembly::operator[](std::string const &symbol) const
{
    return this->symtab_.at(symbol);
}

Symbol Assembly::Lookup(std::string const &symbol)
{
    return this->symtab_[symbol];
}

Assembly::Assembly(NativeMemoryHandle data, NativeMemoryHandle text) : data_(std::move(data)), text_(std::move(text)) {}
