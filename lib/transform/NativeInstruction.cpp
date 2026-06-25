#include "city/transform/NativeInstruction.h"
#include <stdexcept>

using namespace city;

void NativeInstruction::SetPCRelativeTarget(std::size_t pc)
{
    throw std::runtime_error("this instruction type does not support pc-relative targets");
}
