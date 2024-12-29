#ifndef CITY_BLOCK_H
#define CITY_BLOCK_H

#include <memory>
#include <vector>
#include "instruction/IRInstruction.h"
#include "value/Value.h"

namespace city
{
    class Builder;
    class AArch64;
    class Amd64;
    class Function;

    class Block
    {
        friend class Builder;
        friend class AArch64;
        friend class Amd64;

    protected:
        Function *parent_function_;

        std::vector<std::unique_ptr<IRInstruction>> instructions_;
        std::vector<std::unique_ptr<Value>> local_values_;
    };
} // namespace city

#endif // CITY_BLOCK_H
