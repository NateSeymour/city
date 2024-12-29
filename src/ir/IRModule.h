#ifndef CITY_MODULE_H
#define CITY_MODULE_H

#include <memory>
#include <string>
#include <vector>
#include "Block.h"
#include "Builder.h"

namespace city
{
    class AArch64;
    class Amd64;

    class IRModule
    {
        friend class Builder;
        friend class AArch64;
        friend class Amd64;

        std::string name_;

    protected:
        std::vector<std::unique_ptr<Function>> functions_;
        std::vector<std::unique_ptr<Value>> global_values_;
        std::vector<std::unique_ptr<Block>> blocks_;

    public:
        [[nodiscard]] Builder CreateBuilder() noexcept;

        IRModule() = delete;
        IRModule(std::string name);
    };
} // namespace city

#endif // CITY_MODULE_H
