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
        NativeMemoryHandle native_memory_;
        SymbolTable symbol_table_;
        SymbolRefList symbol_refs_;

    public:
        [[nodiscard]] std::size_t GetBinarySize() const noexcept;

        Object(NativeMemoryHandle &&native_memory, SymbolTable &&symbol_table, SymbolRefList &&symbol_refs);
    };
} // namespace city

#endif // OBJECT_H
