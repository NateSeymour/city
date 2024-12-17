#include "x86.h"
#include "ir/Block.h"
#include "ir/Function.h"
#include "ir/instruction/IRInstruction.h"
#include "x86TranslationInterface.h"

using namespace city;

Object x86::BuildModule(Module &module)
{
    Object object;

    x86TranslationInterface translator{object};
    for (auto &function : module.functions_)
    {
        for (auto block : function->blocks_)
        {
            for (auto &instruction : block->instructions_)
            {
                instruction->Apply(&translator);
            }
        }
    }
}
