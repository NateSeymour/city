#ifndef CITY_CALLINST_H
#define CITY_CALLINST_H

#include <city/Function.h>
#include <city/ir/instruction/IRInstruction.h>

namespace city
{
    class CallInst : public IRInstruction
    {
        Function *target_;
        std::vector<Value *> arguments_;

    public:
        [[nodiscard]] Function *GetTarget() const noexcept;
        [[nodiscard]] std::vector<Value *> const &GetArguments() const noexcept;

        void Apply(IRTranslator *interface) override;

        CallInst(Function *target, std::vector<Value *> arguments);
    };
} // namespace city

#endif // CITY_CALLINST_H
