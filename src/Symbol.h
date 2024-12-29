#ifndef CITY_SYMBOL_H
#define CITY_SYMBOL_H

#include <cstddef>
#include <string>
#include <unordered_map>

namespace city
{
    enum class SymbolFlags
    {
        Exectuable = (1 << 0),
    };

    struct Symbol
    {
        std::byte *location;
        SymbolFlags flags;

        template<typename T>
        T *ToPointer() const noexcept
        {
            return reinterpret_cast<T *>(this->location);
        }
    };

    using SymbolTable = std::unordered_map<std::string, Symbol>;
} // namespace city

#endif // CITY_SYMBOL_H
