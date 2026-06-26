//
// Created by Nathan Seymour on 6/25/2026.
//

#ifndef CITY_MODULE_H
#define CITY_MODULE_H

#include <string>
#include <string_view>
#include <list>
#include "Function.h"

namespace city
{
    template<typename ArchitectureT>
    class Module
    {
    protected:
        std::string name_;
        std::list<Function<ArchitectureT>> functions_;

    public:
        [[nodiscard]] Function<ArchitectureT> &CreateFunction(std::string_view const name, Type return_type = Type::Get<void>(), std::vector<Type> const &argument_types = {})
        {
            return this->functions_.emplace_back(name, return_type, argument_types);
        }

        [[nodiscard]] std::optional<Function<ArchitectureT> &> LookupFunction(std::string_view const name) const
        {
            for (auto &function : this->functions_)
            {
                if (function.GetName() == name)
                {
                    return function;
                }
            }

            return std::nullopt;
        }

        Module(std::string_view const name) : name_(name) {}
    };
} // namespace city

#endif // CITY_MODULE_H
