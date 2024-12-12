#include "Function.h"

using namespace city;

Function::Function(std::string name, Type ret, std::vector<Type> const &args, Block *body)
        : name_(std::move(name)), ret_type_(ret), arg_types_(args), body_(body) {}
