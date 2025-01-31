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
        std::vector<std::uint8_t> data_;
        std::vector<std::uint8_t> text_;

        SymbolTable symtab_;
        StubList stubs_;

    public:
        [[nodiscard]] std::size_t GetDataSize() const noexcept;
        [[nodiscard]] std::size_t GetBinarySize() const noexcept;

        Object(std::vector<std::uint8_t> data, std::vector<std::uint8_t> text, SymbolTable symtab, StubList stubs);
    };
} // namespace city

#endif // OBJECT_H
