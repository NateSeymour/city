#include "IRFunction.h"

using namespace city;

IRFunction::IRFunction(Type ret, std::vector<Type> const &args, IRBlock *first_block) : ret_type_(ret), arg_types_(args), first_block_(first_block)
{
    this->blocks_.push_back(this->first_block_);
}
