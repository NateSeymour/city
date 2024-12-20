#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <unordered_map>
#include "Symbol.h"
#include "backend/NativeModule.h"
#include "runtime/NativeMemoryHandle.h"

namespace city
{
    class Object
    {
        NativeMemoryHandle native_memory_;
        std::unordered_map<std::string, Symbol> symtab_;

    public:
        static Object FromNativeModule(NativeModule const &module);

        Object(NativeMemoryHandle native_memory_);
    };
} // namespace city

#endif // OBJECT_H
