#include "city/ir/block/IRConditionalBlock.h"
#include "city/backend/IRTranslator.h"

using namespace city;

void IRConditionalBlock::Apply(IRTranslator &translator)
{
    translator.TranslateBlock(*this);
}

BinaryCondition IRConditionalBlock::GetCondition() const noexcept
{
    return this->condition_;
}

Value *IRConditionalBlock::GetLHS() const noexcept
{
    return this->lhs_;
}

Value *IRConditionalBlock::GetRHS() const noexcept
{
    return this->rhs_;
}

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
