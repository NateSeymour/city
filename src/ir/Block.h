#ifndef CITY_BLOCK_H
#define CITY_BLOCK_H

#include <memory>
#include <vector>
#include "instruction/IRInstruction.h"
#include "value/Value.h"

namespace city
{
    class IRBuilder;
    class AArch64;
    class Amd64;
    class Function;

    class Block
    {
        friend class IRBuilder;
        friend class AArch64;
        friend class Amd64;

    protected:
        Function *parent_function_ = nullptr;

        std::vector<std::unique_ptr<IRInstruction>> instructions_;

    public:
        explicit Block(Function *parent_function);
    };
} // namespace city

#endif // CITY_BLOCK_H
