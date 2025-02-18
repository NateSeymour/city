#include "city/backend/aarch64/AArch64.h"
#include "city/backend/aarch64/AArch64FunctionTranslator.h"
#include "city/ir/IRModule.h"

using namespace city;

NativeModule AArch64::BuildIRModule(IRModule &&ir_module)
{
    NativeModule module{ir_module.GetName(), std::move(ir_module.data_)};

    for (auto &[name, ir_function] : ir_module.functions_)
    {
        std::size_t misalignment = module.AlignPC(16);
        for (std::size_t i = 0; i < misalignment; i++)
        {
            module.text_.push_back(0x69);
        }

        std::size_t function_begin = module.pc_;

        AArch64FunctionTranslator translator{module, *ir_function};
        auto &function = translator.function;

        module.symtab_.try_emplace(name, function, reinterpret_cast<void *>(function_begin));

        for (auto &inst : function.prolog_)
        {
            inst.AppendToBuffer(module.text_);
        }

        for (auto &inst : function.text_)
        {
            inst.AppendToBuffer(module.text_);
        }
    }

    return module;
}
