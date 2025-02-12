#ifndef CITY_AMD64FUNCTION_H
#define CITY_AMD64FUNCTION_H

#include <vector>
#include "city/Function.h"
#include "instruction/Amd64Instruction.h"

namespace city
{
    class Amd64Module;
    class Amd64FunctionTranslator;

    class Amd64Function : public Function
    {
        friend class Amd64Module;
        friend class Amd64FunctionTranslator;

    protected:
        std::vector<Amd64Instruction> prolog_;
        std::vector<Amd64Instruction> text_;

    public:
        Amd64Function(IRFunction const &ir_function);
        Amd64Function(std::string name, Type type, std::vector<Type> argument_types);
    };
} // namespace city

#endif // CITY_AMD64FUNCTION_H
