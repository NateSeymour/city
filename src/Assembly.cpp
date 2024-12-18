#include "Assembly.h"

using namespace city;

Symbol Assembly::Lookup(std::string const &symbol)
{
    return this->symbol_table_[symbol];
}

Assembly::Assembly(NativeMemoryHandle native_memory) : native_memory_(std::move(native_memory)) {}
