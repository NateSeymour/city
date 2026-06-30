#ifndef CITY_COMPILER_H
#define CITY_COMPILER_H

#include <format>
#include <ranges>
#include <string>
#include <unordered_map>

#include "Interop.h"
#include "Symbol.h"
#include "module/Module.h"
#include "runtime/NativeMemoryHandle.h"

namespace city
{
    class JIT
    {
        SymbolTable symbol_table_;
        std::unordered_map<std::string, NativeMemoryHandle> assemblies_;

    public:
        void InsertInterface(std::string_view interface_name, SymbolTable const &symbols)
        {
            for (auto const &[name, symbol] : symbols)
            {
                this->symbol_table_[std::format("{}.{}", interface_name, name)] = symbol;
            }
        }

        template<typename ArchitectureT, typename... PipelineStepTs>
        void InsertModule(Module<ArchitectureT> &&module)
        {

        }

        JIT(JIT &) = delete;
        JIT(bool use_citystd = true)
        {
            if (use_citystd)
            {
                this->InsertInterface("__citystd", {

                });
            }
        }
    };
} // namespace city

#endif // CITY_COMPILER_H
