#include <city/backend/amd64/Amd64.h>
#include <city/backend/amd64/Amd64FunctionTranslator.h>

using namespace city;

Object Amd64::BuildIRModule(IRModule &&ir_module)
{
    Amd64Module amd64_module{ir_module.GetName()};

    for (auto &[name, function] : ir_module.functions_)
    {
        Amd64FunctionTranslator translator{amd64_module, *function};
        amd64_module.functions_.push_back(translator.Translate());
    }

    amd64_module.data_ = std::move(ir_module.data_);

    return amd64_module.Compile();
}
