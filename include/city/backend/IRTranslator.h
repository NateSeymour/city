#ifndef IRTRANSLATOR_H
#define IRTRANSLATOR_H

#include <memory>
#include <span>
#include <vector>

#include "city/container/ConstantDataContainer.h"
#include "city/container/Register.h"
#include "city/container/StackAllocationContainer.h"

#include "city/ir/instruction/arithmetic/AddInst.h"
#include "city/ir/instruction/arithmetic/DivInst.h"
#include "city/ir/instruction/arithmetic/MulInst.h"
#include "city/ir/instruction/arithmetic/SubInst.h"
#include "city/ir/instruction/control/CallInst.h"
#include "city/ir/instruction/control/RetInst.h"

namespace city
{
    class IRTranslator
    {
    protected:
        std::int64_t stack_depth_ = 0;
        std::uint64_t register_dislocation_count_ = 0;
        std::vector<std::unique_ptr<StackAllocationContainer>> stack_;

        void AlignStack(unsigned int alignment) noexcept;

        [[nodiscard]] virtual std::span<Register *> GetScratchRegisterBank(NativeType type) = 0;

        [[nodiscard]] StackAllocationContainer &AcquireStackSpace(Type type);
        [[nodiscard]] Register &AcquireScratchRegister(NativeType type);

    public:
        virtual void TranslateInstruction(AddInst &inst) = 0;
        virtual void TranslateInstruction(DivInst &inst) = 0;
        virtual void TranslateInstruction(MulInst &inst) = 0;
        virtual void TranslateInstruction(SubInst &inst) = 0;
        virtual void TranslateInstruction(CallInst &inst) = 0;
        virtual void TranslateInstruction(RetInst &inst) = 0;

        virtual void Load(Register &dst, ConstantDataContainer &src) = 0;
        virtual void Load(Register &dst, StackAllocationContainer &src) = 0;
        virtual void Load(Register &dst, Register &src) = 0;

        virtual void Store(StackAllocationContainer &dst, Register &src) = 0;
        virtual void Store(Register &dst, Register &src) = 0;

        virtual ~IRTranslator() = default;
    };
} // namespace city

#endif // IRTRANSLATOR_H
