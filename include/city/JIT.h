#ifndef CITY_COMPILER_H
#define CITY_COMPILER_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "Assembly.h"
#include "Object.h"
#include "backend/Backend.h"
#include "ir/IRModule.h"

namespace city
{
    constexpr std::uint32_t kLinkerCanary32 = 0xbeef'0000;
    constexpr std::uint64_t kLinkerCanary64 = 0xcafebeef'00000000;

    class JIT
    {
        std::unique_ptr<Backend> backend_;

        std::unordered_map<std::string, IRModule> ir_modules_;
        std::unordered_map<std::string, Object> objects_;

        /**
         * Translates all IR modules to native modules and deletes the IR modules.
         */
        void CompileIRModules();

        /**
         * Links all objects together (non-destructively) and returns the final linked Assembly.
         * @return Linked Assembly of all stored Objects
         */
        [[nodiscard]] Assembly LinkObjects() const;

    public:
        /**
         * Adds a module to the compiler, transferring ownership to the compiler.
         * @param module Module to transfer to the compiler
         */
        void InsertIRModule(IRModule module);

        /**
         * Removes a module (or corresponding object if already compiled) from the compiler.
         * WARNING: May cause linker errors if other modules depend on the removed module.
         * @param name Name of module to remove
         */
        void RemoveModule(std::string const &name);

        /**
         * Compiles all IR modules to objects and links all objects to one Assembly.
         * Compiled modules are then released. Objects persist until removed (may cause linker errors).
         * @return Compiled Assembly
         */
        [[nodiscard]] Assembly CompileAndLink();

        JIT();
    };
} // namespace city

#endif // CITY_COMPILER_H
