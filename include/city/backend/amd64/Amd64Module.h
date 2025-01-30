#ifndef AMD64MODULE_H
#define AMD64MODULE_H

#include <vector>
#include "instruction/Amd64Instruction.h"

namespace city
{
    struct Amd64Translator;
    struct Amd64RegisterLoader;

    class Amd64Module
    {
        friend class Amd64;
        friend struct Amd64Translator;
        friend struct Amd64RegisterLoader;

        std::vector<Amd64Instruction> instructions_;

    protected:
        void Insert(Amd64Instruction &&inst);
    };
} // namespace city

#endif // AMD64MODULE_H
