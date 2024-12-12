#ifndef CITY_COMPILER_H
#define CITY_COMPILER_H

#include <vector>
#include "Module.h"
#include "Assembly.h"

namespace city
{
    class Compiler
    {
        std::vector<Module *> modules_;

    public:
        void AddModule(Module &module);

        [[nodiscard]] Assembly CompileModules() const;
    };
} // city

#endif //CITY_COMPILER_H
