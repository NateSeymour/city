//
// Created by Nathan on 12/29/2024.
//

#include "Amd64Module.h"
#include "Amd64Builder.h"

using namespace city;

void Amd64Module::InsertInstruction(Amd64Instruction &&inst)
{
    this->instructions_.push_back(inst);
}

Amd64Builder Amd64Module::CreateBuilder()
{
    return Amd64Builder(*this);
}
