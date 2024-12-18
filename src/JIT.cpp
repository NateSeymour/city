#include "JIT.h"

using namespace city;

void JIT::AddModule(std::unique_ptr<Module> module)
{
    this->modules_.push_back(std::move(module));
}

void JIT::RemoveModule(std::string const &name) {}

Assembly JIT::CompileModules()
{
    for (auto &module : this->modules_)
    {
        auto object = this->backend_->BuildModule(*module);
        this->objects_.push_back(std::move(object));
    }

    this->modules_.clear();

    return {};
}

JIT::JIT()
{
    this->backend_ = Backend::CreateHostNative();
}
