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
        NativeMemoryHandle text_;
        SymbolTable symtab_;

    public:
        [[nodiscard]] Symbol operator[](std::string const &symbol) const;
        [[nodiscard]] Symbol Lookup(std::string const &symbol);

        Assembly(NativeMemoryHandle text);
    };
} // namespace city

#endif // CITY_ASSEMBLY_H
