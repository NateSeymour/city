#ifndef CITY_AMD64MODULE_H
#define CITY_AMD64MODULE_H

#include <city/Symbol.h>
#include <city/backend/amd64/instruction/Amd64Instruction.h>
#include <city/ir/IRModule.h>
#include <vector>

namespace city
{
    class Amd64;

    class Amd64Module
    {
        friend class Amd64;

    protected:
        std::string name_;

        std::vector<std::uint8_t> data_;
        std::vector<Amd64Function> functions_;

        StubList stubs_;

    public:
        [[nodiscard]] Object Compile();

        Amd64Module(std::string name);
    };
} // namespace city

#endif // CITY_AMD64MODULE_H
