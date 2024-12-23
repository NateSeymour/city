#ifndef CITY_COMPILER_H
#define CITY_COMPILER_H

#include <memory>
#include <vector>
#include "Assembly.h"
#include "Object.h"
#include "backend/Backend.h"
#include "backend/NativeModule.h"
#include "ir/IRModule.h"

namespace city
{
    class JIT
    {
        std::unique_ptr<Backend> backend_;

        std::vector<IRModule> ir_modules_;
        std::vector<NativeModule> native_modules_;
        std::vector<Object> objects_;

        /**
         * Translates all IR modules to native modules and deletes the IR modules.
         */
        void TranslateIRModules();

        /**
         * Translates all native modules into objects and deletes the native modules.
         */
        void CompileNativeModules();

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
        void AddIRModule(IRModule module);

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
