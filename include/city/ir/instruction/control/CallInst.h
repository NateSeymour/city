#ifndef CITY_CALLINST_H
#define CITY_CALLINST_H

#include <city/Function.h>
#include <city/ir/instruction/IRInstruction.h>

namespace city
{
    class CallInst : public IRInstruction
    {
        std::string target_name_;
        std::vector<Value *> args_;

    public:
        [[nodiscard]] std::string const &GetTargetName() const noexcept;
        [[nodiscard]] std::vector<Value *> const &GetArgs() const noexcept;

        void Apply(IRTranslator *interface) override;

        CallInst(Value *return_value, Function *function, std::vector<Value *> const &args);
    };
} // namespace city

#endif // CITY_CALLINST_H
