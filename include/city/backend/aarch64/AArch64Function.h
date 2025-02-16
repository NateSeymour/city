#ifndef AARCH64FUNCTION_H
#define AARCH64FUNCTION_H

#include "city/Function.h"
#include "city/ir/IRFunction.h"
#include "instruction/AArch64Instruction.h"

namespace city
{
    class AArch64;
    class AArch64FunctionTranslator;

    class AArch64Function : public Function
    {
        friend class AArch64;
        friend class AArch64FunctionTranslator;

    protected:
        std::vector<AArch64Instruction> prolog_;
        std::vector<AArch64Instruction> text_;

    public:
        AArch64Function(IRFunction const &ir_function);
        AArch64Function(std::string name, Type type, std::vector<Type> argument_types);
    };
} // namespace city

#endif // AARCH64FUNCTION_H
