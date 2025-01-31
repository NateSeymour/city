#ifndef CITY_AMD64MODULE_H
#define CITY_AMD64MODULE_H

#include <city/Symbol.h>
#include <city/backend/amd64/instruction/Amd64Instruction.h>
#include <city/ir/IRModule.h>
#include <vector>

namespace city
{
    class Amd64Module
    {
        IRModule &ir_module_;
        SymbolTable symtab_;
        StubList stubs_;
        std::vector<std::uint8_t> data_;
        std::vector<Amd64Instruction> instructions_;

        void TranslateIRFunctions();

    public:
        void Insert(Amd64Instruction &&instruction);

        [[nodiscard]] Object Compile();

        Amd64Module(IRModule &ir_module);
    };
} // namespace city

#endif // CITY_AMD64MODULE_H
