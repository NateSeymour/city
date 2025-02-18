#include <city/backend/amd64/Amd64Function.h>

using namespace city;

Amd64Function::Amd64Function(IRFunction const &ir_function) : Amd64Function(*ir_function.GetName(), ir_function.GetType(), ir_function.GetArgumentTypes()) {}

Amd64Function::Amd64Function(std::string name, Type type, std::vector<Type> argument_types) : Function(std::move(name), type, std::move(argument_types)) {}
