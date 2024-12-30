#ifndef AMD64MODULE_H
#define AMD64MODULE_H

#include <vector>
#include "Amd64.h"
#include "instruction/Amd64Instruction.h"

namespace city
{
    class Amd64Builder;

    class Amd64Module
    {
        friend class Amd64;
        friend class Amd64Builder;

        std::vector<Amd64Instruction> instructions_;

    protected:
        void InsertInstruction(Amd64Instruction &&inst);

    public:
        [[nodiscard]] Amd64Builder CreateBuilder();
    };
} // namespace city

#endif // AMD64MODULE_H
