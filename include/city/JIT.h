#ifndef CITY_COMPILER_H
#define CITY_COMPILER_H

#include <memory>
#include <unordered_map>
#include "Assembly.h"
#include "backend/Backend.h"
#include "interface/InterfaceModule.h"
#include "ir/IRModule.h"

namespace city
{
    class JIT
    {
        std::unordered_map<std::string, InterfaceModule> interfaces_;
        std::unordered_map<std::string, NativeModule> modules_;

    public:
        /**
         * Adds an interface module to the compiler.
         * @param module Module to transfer to the compiler
         */
        void InsertInterfaceModule(InterfaceModule &&module);

        /**
         * Adds an IR module to the compiler and compiles it directly to Object.
         * @param module Module to transfer to the compiler
         */
        void InsertIRModule(IRModule &&module);

        /**
         * Removes a module (or corresponding object if already compiled) from the compiler.
         * WARNING: May cause linker errors if other modules depend on the removed module.
         * @param name Name of module to remove
         */
        void RemoveModule(std::string const &name);

        /**
         * Links all objects together (non-destructively) and returns the final linked Assembly.
         * @return Linked Assembly of all stored Objects
         */
        [[nodiscard]] Assembly Link() const;
    };
} // namespace city

#endif // CITY_COMPILER_H
