#ifndef CITY_ASSEMBLY_H
#define CITY_ASSEMBLY_H

#include <string>
#include "Symbol.h"
#include "runtime/NativeMemoryHandle.h"

namespace city
{
    class JIT;

    class Assembly
    {
        friend class JIT;

    protected:
        NativeMemoryHandle native_memory_;
        SymbolTable symbol_table_;
        SymbolRefList symbol_refs_;

    public:
        [[nodiscard]] Symbol operator[](std::string const &symbol) const;
        [[nodiscard]] Symbol Lookup(std::string const &symbol);

        Assembly(NativeMemoryHandle native_memory);
    };
} // namespace city

#endif // CITY_ASSEMBLY_H
