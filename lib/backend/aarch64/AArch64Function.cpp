#include "city/backend/aarch64/AArch64Function.h"

using namespace city;

AArch64Function::AArch64Function(IRFunction const &ir_function) : AArch64Function(*ir_function.GetName(), ir_function.GetType(), ir_function.GetArgumentTypes()) {}

AArch64Function::AArch64Function(std::string name, Type type, std::vector<Type> argument_types) : Function(std::move(name), type, std::move(argument_types)) {}
