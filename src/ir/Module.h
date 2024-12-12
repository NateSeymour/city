#ifndef CITY_MODULE_H
#define CITY_MODULE_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include "Symbol.h"
#include "Builder.h"
#include "Block.h"

namespace city
{
    class Module
    {
        friend class Builder;

        std::string name_;

    protected:
        std::vector<std::unique_ptr<Function>> functions_;
        std::vector<std::unique_ptr<Value>> global_values_;
        std::vector<std::unique_ptr<Block>> blocks_;

    public:
        [[nodiscard]] Builder CreateBuilder() noexcept;

        Module() = delete;
        Module(std::string name);
    };
} // city

#endif //CITY_MODULE_H
