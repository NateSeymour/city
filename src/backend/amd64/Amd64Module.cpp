//
// Created by Nathan on 12/29/2024.
//

#include "Amd64Module.h"

using namespace city;

void Amd64Module::Insert(Amd64Instruction &&inst)
{
    this->instructions_.push_back(inst);
}
