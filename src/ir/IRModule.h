#ifndef CITY_MODULE_H
#define CITY_MODULE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "Block.h"
#include "IRBuilder.h"

namespace city
{
    class AArch64;
    class Amd64;

    class IRModule
    {
        friend class IRBuilder;
        friend class AArch64;
        friend class Amd64;

        std::string name_;

    protected:
        std::unordered_map<std::string, std::unique_ptr<Function>> functions_;
        std::unordered_map<std::string, std::unique_ptr<Value>> global_values_;
        std::vector<std::unique_ptr<Block>> blocks_;

    public:
        [[nodiscard]] std::string const &GetName() const noexcept;

        [[nodiscard]] IRBuilder CreateBuilder() noexcept;

        IRModule() = delete;
        IRModule(std::string name);
    };
} // namespace city

#endif // CITY_MODULE_H
