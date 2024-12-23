#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <unordered_map>
#include "backend/NativeModule.h"
#include "runtime/NativeMemoryHandle.h"

namespace city
{
    class JIT;

    class Object
    {
        friend class JIT;

    protected:
        NativeMemoryHandle native_memory_;

        /**
         * Holds instruction labels with their offsets into the binary.
         */
        std::unordered_map<std::string, std::size_t> symtab_;

    public:
        [[nodiscard]] std::size_t GetBinarySize() const noexcept;

        static Object FromNativeModule(NativeModule const &module);

        Object(NativeMemoryHandle native_memory);
    };
} // namespace city

#endif // OBJECT_H
