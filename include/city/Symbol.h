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

    enum class StubSourceLocation
    {
        Text,
        Data,
    };

    /**
     * A Stub is a reference to an anonymous/named symbol that the linker should generate a pointer to.
     */
    struct Stub
    {
        /**
         * Label to the named symbol that is referenced. If used, src_offset will be ignored.
         */
        std::optional<std::string> label = std::nullopt;

        /**
         * Offset into the section designated by StubSourceLocation where the linker should generate an address to.
         */
        std::size_t src_offset = 0;

        /**
         * Binary section to link to.
         */
        StubSourceLocation type;

        /**
         * Offset into the text section where the stub is to be resolved.
         */
        std::size_t dst_offset = 0;

        /**
         * Index of this stub in the StubList it belongs to.
         */
        std::size_t index = 0;

        /**
         * Data type of source data (equivalent of *data).
         */
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
