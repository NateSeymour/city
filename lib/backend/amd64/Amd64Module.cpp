#include <city/backend/amd64/Amd64Module.h>

using namespace city;

void Amd64Module::Insert(Amd64Instruction &&inst)
{
    this->instructions_.push_back(inst);
}
