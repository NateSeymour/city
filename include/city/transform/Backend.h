#ifndef CITY_BACKEND_H
#define CITY_BACKEND_H

#include "NativeModule.h"
#include "city/ir/IRModule.h"

namespace city
{
    class Backend
    {
        template<typename TranslatorType>
        static NativeModule Compile(IRModule &&ir_module)
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

                TranslatorType translator{module, *ir_function};
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

    public:
        [[nodiscard]] static NativeModule CompileToNative(IRModule &&ir_module);
    };
} // namespace city

#endif // CITY_BACKEND_H
