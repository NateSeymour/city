#ifndef CITY_COMPILER_H
#define CITY_COMPILER_H

#include <vector>
#include "Module.h"
#include "Object.h"

namespace city
{
    class Compiler
    {
        std::vector<Module *> modules_;

    public:
        void AddModule(Module &module);

        [[nodiscard]] Object CompileModules() const;
    };
} // city

#endif //CITY_COMPILER_H
