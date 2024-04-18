//
// Created by bachia on 4/17/2024.
//

#include "../include/Oasis/Mod.hpp"
#include "../include/Oasis/Derivative.hpp"
#include "Oasis/Add.hpp"
#include "Oasis/Divide.hpp"
#include "Oasis/Exponent.hpp"
#include "Oasis/Expression.hpp"
#include "Oasis/Log.hpp"
#include "Oasis/Multiply.hpp"
#include "Oasis/Real.hpp"
#include "Oasis/Subtract.hpp"
#include "Oasis/Undefined.hpp"
#include "string"
#include <cmath>

namespace Oasis {
    Mod<Expression>::Mod(const Expression& Op1, const Expression& Op2)
            : BinaryExpression(Op1, Op2)
    {
    }

    auto Mod<Expression>::Simplify() const -> std::unique_ptr<Expression>
    {
        auto simplifiedOpOne = mostSigOp ? mostSigOp->Simplify() : nullptr;
        auto simplifiedOpTwo = leastSigOp ? leastSigOp->Simplify() : nullptr;
        Mod simplifiedMod { *simplifiedOpOne, *simplifiedOpTwo };
        if (auto realCase = Mod<Real>::Specialize(simplifiedMod); realCase != nullptr) {
            const Real& firstReal = realCase->GetMostSigOp();
            const Real& secondReal = realCase->GetLeastSigOp();
            return std::make_unique<Real>(((int)(firstReal.GetValue()) % ((int)secondReal.GetValue())));
        }
        return simplifiedMod.Copy();
    }
    auto Mod<Expression>::ToString() const -> std::string
    {
        return fmt::format("({} % {})", mostSigOp->ToString(), leastSigOp->ToString());
    }
    auto Mod<Expression>::Specialize(const Expression& other) -> std::unique_ptr<Mod<Expression, Expression>>
    {
        if (!other.Is<Oasis::Mod>()) {
            return nullptr;
        }

        auto otherGeneralized = other.Generalize();
        return std::make_unique<Mod>(dynamic_cast<const Mod&>(*otherGeneralized));
    }

    auto Mod<Expression>::Specialize(const Expression& other, tf::Subflow& subflow) -> std::unique_ptr<Mod>
    {
        if (!other.Is<Oasis::Mod>()) {
            return nullptr;
        }

        auto otherGeneralized = other.Generalize(subflow);
        return std::make_unique<Mod>(dynamic_cast<const Mod&>(*otherGeneralized));
    }
}
