#ifndef CITY_MODULE_H
#define CITY_MODULE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "../container/ConstantDataContainer.h"
#include "IRBuilder.h"

namespace city
{
    class Amd64;

    class IRModule
    {
        friend class IRBuilder;
        friend class Amd64;

        std::string name_;

    protected:
        std::vector<std::uint8_t> data_;
        std::unordered_map<std::string, std::unique_ptr<IRFunction>> functions_;
        std::unordered_map<std::string, std::unique_ptr<Value>> global_values_;
        std::vector<std::unique_ptr<ConstantDataContainer>> global_constants_;

    public:
        [[nodiscard]] std::string const &GetName() const noexcept;

        [[nodiscard]] IRBuilder CreateBuilder() noexcept;

        IRModule() = delete;
        IRModule(std::string name);
    };
} // namespace city

#endif // CITY_MODULE_H
