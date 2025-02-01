#include <city/backend/amd64/Amd64.h>
#include <city/backend/amd64/Amd64FunctionTranslator.h>

using namespace city;

Object Amd64::BuildModule(IRModule &ir_module)
{
    Amd64Module amd64_module{ir_module};

    return amd64_module.Compile();
}
