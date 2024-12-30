#include "Function.h"

using namespace city;

Function::Function(Type ret, std::vector<Type> const &args, Block *first_block) : ret_type_(ret), arg_types_(args), first_block_(first_block)
{
    this->blocks_.push_back(this->first_block_);
}
