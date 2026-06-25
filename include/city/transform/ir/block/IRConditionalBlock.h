#ifndef IRCONDITIONALBLOCK_H
#define IRCONDITIONALBLOCK_H

#include "IRBlock.h"
#include "city/ir/IRCondition.h"

namespace city
{
    class IRConditionalBlock : public IRBlock
    {
    protected:
        Value *cmp_ = nullptr;
        BinaryCondition condition_;

        /// Block to be executed if the condition evaluates TRUE.
        std::unique_ptr<IRBlock> true_block_;

        /// Block to be executed if the condition evaluates FALSE.
        std::unique_ptr<IRBlock> else_block_;

        void Apply(IRTranslator &translator) override;

    public:
        [[nodiscard]] BinaryCondition GetCondition() const noexcept;

        [[nodiscard]] Value *GetCMP() const noexcept;

        [[nodiscard]] IRBlock &GetTrueBlock() const;
        [[nodiscard]] IRBlock &GetElseBlock() const;

        IRConditionalBlock(IRFunction &parent, Value *cmp, BinaryCondition condition);
    };
} // namespace city

#endif // IRCONDITIONALBLOCK_H
