#include "city/backend/amd64/Amd64.h"
#include "city/backend/amd64/Amd64FunctionTranslator.h"

using namespace city;

NativeModule Amd64::BuildIRModule(IRModule &&ir_module)
{
    Amd64Module amd64_module{ir_module.GetName(), std::move(ir_module.data_)};

    for (auto &[name, function] : ir_module.functions_)
    {
        Amd64FunctionTranslator translator{amd64_module, *function};
        amd64_module.functions_.push_back(translator.Translate());
    }

    return amd64_module;
}
