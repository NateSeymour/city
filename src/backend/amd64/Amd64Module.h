#ifndef AMD64MODULE_H
#define AMD64MODULE_H

#include <vector>
#include "Amd64.h"
#include "instruction/Amd64Instruction.h"

namespace city
{
    struct Amd64Translator;

    class Amd64Module
    {
        friend class Amd64;
        friend class Amd64Translator;

        // std::stack stack_;
        std::vector<Amd64Instruction> instructions_;
        std::array<Amd64Register, 8> registers_ = amd64_register_definitions;

    protected:
        void InsertInstruction(Amd64Instruction &&inst);


    public:
    };
} // namespace city

#endif // AMD64MODULE_H
