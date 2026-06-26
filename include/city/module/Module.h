//
// Created by Nathan Seymour on 6/25/2026.
//

#ifndef CITY_MODULE_H
#define CITY_MODULE_H

#include <string>
#include <unordered_map>
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
        std::unordered_map<std::string, std::reference_wrapper<Function<ArchitectureT>>> function_table_;
    };
} // namespace city

#endif // CITY_MODULE_H
