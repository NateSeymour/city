#ifndef CITY_AMD64FUNCTION_H
#define CITY_AMD64FUNCTION_H

#include <string>
#include <vector>
#include "instruction/Amd64Instruction.h"

namespace city
{
    class Amd64Function
    {
        std::string name_;

        std::vector<Amd64Instruction> prolog_;
        std::vector<Amd64Instruction> text_;
        std::vector<Amd64Instruction> epilog_;
    };
} // namespace city

#endif // CITY_AMD64FUNCTION_H
