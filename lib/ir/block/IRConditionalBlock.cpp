#include "city/ir/block/IRConditionalBlock.h"

using namespace city;

IRBlock &IRConditionalBlock::GetTrueBlock() const
{
    return *this->true_block_;
}

IRBlock &IRConditionalBlock::GetElseBlock() const
{
    return *this->else_block_;
}

IRConditionalBlock::IRConditionalBlock(IRFunction &parent, Value *lhs, BinaryCondition condition, Value *rhs) : IRBlock(parent), lhs_(lhs), condition_(condition), rhs_(rhs)
{
    this->true_block_ = std::make_unique<IRBlock>(parent);
    this->else_block_ = std::make_unique<IRBlock>(parent);

    // Terminated, because no instructions should be added to a conditional block.
    this->terminated_ = true;
}
