#ifndef CITY_SYMBOL_H
#define CITY_SYMBOL_H

#include <cstddef>

namespace city
{
    enum class SymbolFlags
    {
        Exectuable = (1 << 0),
    };

    struct Symbol
    {
        std::byte *raw;
        SymbolFlags flags;
    };
} // namespace city

#endif // CITY_SYMBOL_H
