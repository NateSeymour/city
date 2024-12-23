#ifndef CITY_ASSEMBLY_H
#define CITY_ASSEMBLY_H

#include <string>
#include <unordered_map>
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
        std::unordered_map<std::string, Symbol> symbol_table_;

    public:
        [[nodiscard]] Symbol Lookup(std::string const &symbol);

        Assembly(NativeMemoryHandle native_memory);
    };
} // namespace city

#endif // CITY_ASSEMBLY_H
