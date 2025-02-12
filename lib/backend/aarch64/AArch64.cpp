#include "city/backend/aarch64/AArch64.h"
#include "city/Object.h"
#include "city/backend/aarch64/AArch64FunctionTranslator.h"
#include "city/backend/aarch64/AArch64Module.h"
#include "city/ir/IRModule.h"

using namespace city;

Object AArch64::BuildIRModule(IRModule &&ir_module)
{
    AArch64Module aarch64_module{ir_module.GetName(), std::move(ir_module.data_)};

    for (auto &[name, function] : ir_module.functions_)
    {
        AArch64FunctionTranslator translator{aarch64_module, *function};
        aarch64_module.functions_.push_back(std::move(translator.function));
    }

    return aarch64_module.Compile();
}
