#ifndef OBJECT_H
#define OBJECT_H

#include "Symbol.h"
#include "runtime/NativeMemoryHandle.h"

namespace city
{
    class JIT;

    class Object
    {
        friend class JIT;

    protected:
        std::vector<std::byte> data_;
        NativeMemoryHandle text_;

        SymbolTable symbol_table_;
        SymbolRefList symbol_refs_;

    public:
        [[nodiscard]] std::size_t GetBinarySize() const noexcept;

        Object(NativeMemoryHandle &&text, NativeMemoryHandle &&data, SymbolTable &&symbol_table, SymbolRefList &&symbol_refs);
    };
} // namespace city

#endif // OBJECT_H
