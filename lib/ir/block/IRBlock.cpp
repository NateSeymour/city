#include <city/ir/block/IRBlock.h>

using namespace city;

std::vector<std::unique_ptr<IRInstruction>> const &IRBlock::GetInstructions() const noexcept
{
    return this->instructions_;
}

IRBlock::IRBlock(IRFunction &parent_function) : parent_function_(parent_function) {}
