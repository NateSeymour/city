#ifndef CITY_IRBLOCK_H
#define CITY_IRBLOCK_H

#include <memory>
#include <optional>
#include <vector>
#include "ir/instruction/IRInstruction.h"
#include "value/Value.h"

namespace city
{
    class IRBuilder;
    class AArch64;
    class Amd64;
    class IRFunction;

    class IRBlock
    {
        friend class IRBuilder;
        friend class AArch64;
        friend class Amd64;

    protected:
        IRFunction &parent_function_;

        std::vector<std::unique_ptr<IRInstruction>> instructions_;

    public:
        explicit IRBlock(IRFunction &parent_function);
    };
} // namespace city

#endif // CITY_IRBLOCK_H
