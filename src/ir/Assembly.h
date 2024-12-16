#ifndef CITY_ASSEMBLY_H
#define CITY_ASSEMBLY_H

#include <string>
#include <unordered_map>
#include "Symbol.h"

namespace city
{
    class Assembly
    {
        std::unordered_map<std::string, Symbol> symbol_table_;

    public:
        [[nodiscard]] Symbol Lookup(std::string const &symbol);
    };
} // city

#endif //CITY_ASSEMBLY_H
