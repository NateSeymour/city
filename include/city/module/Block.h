//
// Created by Nathan Seymour on 6/25/2026.
//

#ifndef CITY_BLOCK_H
#define CITY_BLOCK_H

#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include <optional>
#include "Value.h"

namespace city
{
    /**
     * A Block represents a single, reentrant, non-branching strand of execution.
     * @tparam ArchitectureT
     */
    template <typename ArchitectureT>
    class Block
    {
    protected:
        std::optional<Block &> parent_;
        std::uint64_t level_ = 0;

        std::list<Value> values_;
        std::unordered_map<std::string, std::reference_wrapper<Value>> locals_;

        std::list<Block> children_;

    public:
        Block(Block &parent) : parent_(parent), level_(parent.level_ + 1) {}
        Block() : parent_(std::nullopt) {}
    };
} // namespace city

#endif // CITY_BLOCK_H
