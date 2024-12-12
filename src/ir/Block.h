#ifndef CITY_BLOCK_H
#define CITY_BLOCK_H

#include <vector>
#include <memory>
#include "value/Value.h"
#include "instruction/Instruction.h"

namespace city
{
    class Block
    {
        std::vector<std::unique_ptr<Instruction>> instructions_;
        std::vector<std::unique_ptr<Value>> local_values_;
    };
} // city

#endif //CITY_BLOCK_H
