//
// Created by bachia on 4/17/2024.
//

#ifndef OASIS_MOD_HPP
#define OASIS_MOD_HPP

#include "fmt/core.h"

#include "BinaryExpression.hpp"
#include "Expression.hpp"
#include "Real.hpp"

namespace Oasis {

    template <IExpression Op1, IExpression Op2>
    class Mod;

/// @cond
    template <>
    class Mod<Expression, Expression> : public BinaryExpression<Mod> {
    public:
        Mod() = default;
        Mod(const Mod<Expression, Expression>& other) = default;

        Mod(const Expression& Exp, const Expression& Var);

        [[nodiscard]] auto Simplify() const -> std::unique_ptr<Expression> final;
        // auto Simplify(tf::Subflow& subflow) const -> std::unique_ptr<Expression> final;

        [[nodiscard]] auto ToString() const -> std::string final;

        static auto Specialize(const Expression& other) -> std::unique_ptr<Mod>;
        static auto Specialize(const Expression& other, tf::Subflow& subflow) -> std::unique_ptr<Mod>;

        EXPRESSION_TYPE(Mod)
        EXPRESSION_CATEGORY(0)
    };
/// @endcond

/**
 * The Mod expression mods Op1 by Op2 - aka, Op1 % Op2
 *
 * @tparam Op1 The expression to be modded.
 * @tparam Op2 The expression to be the base of the mod.
 */
    template <IExpression Op1 = Expression, IExpression Op2 = Op1>
    class Mod : public BinaryExpression<Mod, Op1, Op2> {
    public:
        Mod() = default;
        Mod(const Mod<Op1, Op2>& other)
                : BinaryExpression<Mod, Op1, Op2>(other)
        {
        }

        Mod(const Op1& exp, const Op2& var)
                : BinaryExpression<Mod, Op1, Op2>(exp, var)
        {
        }

        [[nodiscard]] auto ToString() const -> std::string final
        {
            return fmt::format("({} % {})", this->mostSigOp->ToString(), this->leastSigOp->ToString());
        }

        IMPL_SPECIALIZE(Mod, Op1, Op2)

        auto operator=(const Mod& other) -> Mod& = default;

        EXPRESSION_TYPE(Mod)
        EXPRESSION_CATEGORY(0)
    };

} // namespace Oasis


#endif //OASIS_MOD_HPP
