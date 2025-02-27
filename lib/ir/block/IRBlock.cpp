#include <city/ir/block/IRBlock.h>

using namespace city;

bool IRBlock::IsConditional() const noexcept
{
    return this->conditional_;
}

IRBlock *IRBlock::GetPredecessor() const noexcept
{
    return this->predecessor_;
}

IRBlock *IRBlock::GetSuccessor() const noexcept
{
    return this->successor_.get();
}

void IRBlock::SetConditional(bool conditional)
{
    this->conditional_ = conditional;
}

IRBlock &IRBlock::InsertBlock(bool terminate)
{
    auto new_block = std::make_unique<IRBlock>(this->parent_, this);

    if (this->successor_ != nullptr)
    {
        this->successor_->predecessor_ = new_block.get();
        new_block->successor_ = std::move(this->successor_);
    }

    this->successor_ = std::move(new_block);
    return *this->successor_;
}

std::vector<std::unique_ptr<IRInstruction>> const &IRBlock::GetInstructions() const noexcept
{
    return this->instructions_;
}

IRBlock::IRBlock(IRFunction &parent, IRBlock *predecessor) : parent_(parent), predecessor_(predecessor) {}
