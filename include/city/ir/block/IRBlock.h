#ifndef CITY_IRBLOCK_H
#define CITY_IRBLOCK_H

#include <memory>
#include <vector>
#include "city/ir/instruction/IRInstruction.h"

namespace city
{
    class IRBuilder;
    class IRFunction;
    class Amd64FunctionTranslator;

    class IRBlock
    {
        friend class IRBuilder;
        friend class Amd64FunctionTranslator;

    protected:
        IRFunction &parent_function_;

        std::vector<std::unique_ptr<IRInstruction>> instructions_;

    public:
        [[nodiscard]] std::vector<std::unique_ptr<IRInstruction>> const &GetInstructions() const noexcept;

        explicit IRBlock(IRFunction &parent_function);
    };
} // namespace city

#endif // CITY_IRBLOCK_H
