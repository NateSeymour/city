#ifndef CITY_AMD64FUNCTION_H
#define CITY_AMD64FUNCTION_H

#include <string>
#include <vector>
#include "instruction/Amd64Instruction.h"

namespace city
{
    class Amd64FunctionTranslator;

    class Amd64Function
    {
        friend class Amd64FunctionTranslator;

    protected:
        std::string name_;

        std::vector<Amd64Instruction> prolog_;
        std::vector<Amd64Instruction> text_;

    public:
        Amd64Function(std::string name);
    };
} // namespace city

#endif // CITY_AMD64FUNCTION_H
