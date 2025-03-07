#include "city/ir/block/IRBlock.h"
#include "city/backend/IRTranslator.h"
#include "city/ir/block/IRConditionalBlock.h"

using namespace city;

IRBlock *IRBlock::GetSuccessor() const noexcept
{
    return this->successor_.get();
}

IRBlock &IRBlock::InsertBlock()
{
    auto new_block = std::make_shared<IRBlock>(this->parent_);

    if (this->successor_ != nullptr)
    {
        new_block->successor_ = std::move(this->successor_);
    }

    this->successor_ = std::move(new_block);
    return *this->successor_;
}

IRConditionalBlock &IRBlock::InsertConditionalBlock(Value *lhs, BinaryCondition condition, Value *rhs)
{
    auto new_block = std::make_shared<IRConditionalBlock>(this->parent_, lhs, condition, rhs);

    if (this->successor_ != nullptr)
    {
        new_block->successor_ = std::move(this->successor_);
    }

    this->successor_ = std::move(new_block);
    return dynamic_cast<IRConditionalBlock &>(*this->successor_);
}

void IRBlock::Apply(IRTranslator &translator)
{
    translator.TranslateBlock(*this);
}

std::vector<std::unique_ptr<IRInstruction>> const &IRBlock::GetInstructions() const noexcept
{
    return this->instructions_;
}

IRBlock::IRBlock(IRFunction &parent) : parent_(parent) {}
