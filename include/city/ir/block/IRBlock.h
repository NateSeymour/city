#ifndef CITY_IRBLOCK_H
#define CITY_IRBLOCK_H

#include <memory>
#include <vector>
#include "city/ir/instruction/IRInstruction.h"

namespace city
{
    class IRBuilder;
    class IRFunction;

    /**
     * Represents a simple block of IR code. Implemented as a doubly-linked list.
     * Each block owns its successor and holds a pointer to its predecessor.
     * Each block may contain only one branching instruction (with the exception of subroutine calls). This is enforced by it IR builder.
     * This branching instruction should be the final instruction of the block.
     * If a block does not end in a branching instruction, then it is assumed that a fall-through to its successor is desired.
     *
     * Additionally, a block must be marked as conditional if it is not always called.
     */
    class IRBlock
    {
        friend class IRBuilder;
        friend class IRFunction;

    protected:
        IRFunction &parent_;

        /// Indicates that this block is only executed following a condition.
        bool conditional_ = false;

        /// Indicates that this block is finished and no more instructions may be added.
        bool terminated_ = false;

        /// The block before this one in the parent function. Is `nullptr` if this is the first block.
        IRBlock *predecessor_ = nullptr;

        /// Block that follows this function.
        std::unique_ptr<IRBlock> successor_ = nullptr;

        std::vector<std::unique_ptr<IRInstruction>> instructions_;

        template<typename T, typename... Args>
        [[nodiscard]] T *InsertInstruction(Args... args)
        {
            if (!this->terminated_)
            {
                auto &inst = this->instructions_.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
                return dynamic_cast<T *>(inst.get());
            }

            return nullptr;
        }

        void SetConditional(bool conditional);

        /**
         * Inserts a new block following this one, optionally terminating the current block.
         * @param terminate Terminate the current block.
         * @return
         */
        [[nodiscard]] IRBlock &InsertBlock(bool terminate = true);

    public:
        [[nodiscard]] bool IsConditional() const noexcept;

        [[nodiscard]] IRBlock *GetPredecessor() const noexcept;
        [[nodiscard]] IRBlock *GetSuccessor() const noexcept;

        [[nodiscard]] std::vector<std::unique_ptr<IRInstruction>> const &GetInstructions() const noexcept;

        explicit IRBlock(IRFunction &parent, IRBlock *predecessor = nullptr);
    };
} // namespace city

#endif // CITY_IRBLOCK_H
