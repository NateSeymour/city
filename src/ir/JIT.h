#ifndef CITY_COMPILER_H
#define CITY_COMPILER_H

#include <memory>
#include <vector>
#include "Assembly.h"
#include "Module.h"
#include "Object.h"
#include "backend/Backend.h"

namespace city
{
    class JIT
    {
        std::unique_ptr<Backend> backend_;
        std::vector<std::unique_ptr<Module>> modules_;
        std::vector<Object> objects_;

    public:
        /**
         * Adds a module to the compiler, transferring ownership to the compiler.
         * @param module Module to transfer to the compiler
         */
        void AddModule(std::unique_ptr<Module> module);

        /**
         * Compiles all IR modules to objects and links all objects to one Assembly.
         * Compiled modules are then released. Objects persist until removed (may cause linker errors).
         * @return Compiled Assembly
         */
        [[nodiscard]] Assembly CompileModules();

        JIT();
    };
} // namespace city

#endif // CITY_COMPILER_H
