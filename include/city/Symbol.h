#ifndef CITY_SYMBOL_H
#define CITY_SYMBOL_H

#include <city/type/Type.h>
#include <cstddef>
#include <expected>
#include <string>
#include <unordered_map>
#include <vector>

namespace city
{
    enum class SymbolFlags
    {
        None = 0,
        Executable = (1 << 0),
    };

    enum class StubType
    {
        Text,
        Data,
    };

    struct Stub
    {
        std::optional<std::string> label = std::nullopt;
        std::size_t offset = 0;
        StubType type;
        Type data_type;

        [[nodiscard]] bool IsAnonymous() const noexcept;
    };

    using StubList = std::vector<Stub>;

    struct Symbol
    {
        std::byte *location = nullptr;
        SymbolFlags flags = SymbolFlags::None;
        Type type;

        template<typename T>
        T *ToPointer() const noexcept
        {
            return reinterpret_cast<T *>(this->location);
        }
    };

    using SymbolTable = std::unordered_map<std::string, Symbol>;
} // namespace city

#endif // CITY_SYMBOL_H
