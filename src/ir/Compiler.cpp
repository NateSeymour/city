#include "Compiler.h"

using namespace city;

void Compiler::AddModule(Module &module)
{
    this->modules_.push_back(&module);
}

Object  Compiler::CompileModules() const
{
    return {};
}
