#ifndef CITY_IRBLOCK_H
#define CITY_IRBLOCK_H

#include <city/Value.h>
#include <city/ir/instruction/IRInstruction.h>
#include <memory>
#include <optional>
#include <vector>

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
        explicit IRBlock(IRFunction &parent_function);
    };
} // namespace city

#endif // CITY_IRBLOCK_H
