#ifndef AMD64MODULE_H
#define AMD64MODULE_H

#include <vector>
#include "instruction/Amd64Instruction.h"

namespace city
{
    class Amd64Translator;

    class Amd64Module
    {
        friend class Amd64;
        friend class Amd64Translator;

        std::vector<Amd64Instruction> instructions_;

    protected:
        void Insert(Amd64Instruction &&inst);
    };
} // namespace city

#endif // AMD64MODULE_H
