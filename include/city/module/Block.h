//
// Created by Nathan Seymour on 6/25/2026.
//

#ifndef CITY_BLOCK_H
#define CITY_BLOCK_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Value.h"

namespace city
{
    template <typename ArchitectureT>
    class Block
    {
    protected:
        std::unordered_map<std::string, Value> locals_;
        std::vector<Value> values_;
        std::vector<Block<ArchitectureT>> children_;

        std::vector<typename ArchitectureT::Instruction> instructions_;
    };
} // namespace city

#endif // CITY_BLOCK_H
