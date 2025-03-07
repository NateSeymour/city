#include "city/backend/aarch64/AArch64Condition.h"

using namespace city;

std::map<BinaryCondition, AArch64Condition> const city::AArch64ConditionTranslationMap = {
        {BinaryCondition::EqualTo, AArch64Condition::EQ},

        {BinaryCondition::GreaterThan, AArch64Condition::GT},
        {BinaryCondition::LessThan, AArch64Condition::LT},

        {BinaryCondition::GreaterOrEqualTo, AArch64Condition::GE},
        {BinaryCondition::LessOrEqualTo, AArch64Condition::LE},
};
