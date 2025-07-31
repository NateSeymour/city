#include <city/backend/Backend.h>

using namespace city;

NativeModule Backend::CompileToNative(IRModule &&ir_module)
{
#if defined(__x86_64__) || defined(_WIN64)
    return Backend::Compile<Amd64FunctionTranslator>(std::move(ir_module));
#elif defined(__aarch64__)
    return Backend::Compile<AArch64FunctionTranslator>(std::move(ir_module));
#endif
}
