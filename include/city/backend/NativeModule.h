#ifndef NATIVEMODULE_H
#define NATIVEMODULE_H

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include "city/Symbol.h"

namespace city
{
    class JIT;

    class Backend;

    class IRTranslator;
    class Amd64FunctionTranslator;
    class AArch64FunctionTranslator;

    class NativeModule
    {
        friend class JIT;

        friend class Backend;

        friend class IRTranslator;
        friend class Amd64FunctionTranslator;
        friend class AArch64FunctionTranslator;

    protected:
        std::string name_;
        std::vector<std::uint8_t> cdata_;
        std::map<std::string, std::size_t> stubs_;
        std::vector<std::uint8_t> text_;

        SymbolTable symtab_;

        std::size_t pc_ = 0;

        std::size_t AlignPC(std::size_t alignment = 16);

    public:
        [[nodiscard]] std::size_t GetBinarySize() const noexcept;

        NativeModule(std::string name, std::vector<std::uint8_t> cdata);
        virtual ~NativeModule() = default;
    };
} // namespace city

#endif // NATIVEMODULE_H
