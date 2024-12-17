#ifndef CITY_BLOCK_H
#define CITY_BLOCK_H

#include <memory>
#include <vector>
#include "Function.h"
#include "instruction/IRInstruction.h"
#include "value/Value.h"

namespace city
{
    class Builder;
    class AArch64;
    class x86;

    class Block
    {
        friend class Builder;
        friend class AArch64;
        friend class x86;

    protected:
        Function *parent_function_;

        std::vector<std::unique_ptr<IRInstruction>> instructions_;
        std::vector<std::unique_ptr<Value>> local_values_;
    };
} // namespace city

#endif // CITY_BLOCK_H
