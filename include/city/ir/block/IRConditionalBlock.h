#ifndef IRCONDITIONALBLOCK_H
#define IRCONDITIONALBLOCK_H

#include "IRBlock.h"
#include "city/ir/IRCondition.h"

namespace city
{
    class IRConditionalBlock : public IRBlock
    {
    protected:
        Value *lhs_ = nullptr;
        BinaryCondition condition_;
        Value *rhs_ = nullptr;

        /// Block to be executed if the condition evaluates TRUE.
        std::unique_ptr<IRBlock> true_block_;

        /// Block to be executed if the condition evaluates FALSE.
        std::unique_ptr<IRBlock> else_block_;

        void Apply(IRTranslator &translator) override;

    public:
        [[nodiscard]] BinaryCondition GetCondition() const noexcept;

        [[nodiscard]] Value *GetLHS() const noexcept;
        [[nodiscard]] Value *GetRHS() const noexcept;

        [[nodiscard]] IRBlock &GetTrueBlock() const;
        [[nodiscard]] IRBlock &GetElseBlock() const;

        IRConditionalBlock(IRFunction &parent, Value *lhs, BinaryCondition condition, Value *rhs);
    };
} // namespace city

#endif // IRCONDITIONALBLOCK_H
