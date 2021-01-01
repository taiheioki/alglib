#ifndef ALGLIB_UTIL_FIX_POINT_HPP_
#define ALGLIB_UTIL_FIX_POINT_HPP_

#include <utility>

namespace alg
{
// Helper class for recursively calling lambda expressions.
// Reference: http://koturn.hatenablog.com/entry/2018/06/10/060000
template<class F>  // NO-FORMAT
struct FixPoint : private F
{
    template<class G>
    explicit constexpr FixPoint(G&& g) noexcept : F{std::forward<G>(g)}
    {}

    template<class... Args>
    constexpr decltype(auto) operator()(Args&&... args) const
    {
        return F::operator()(*this, std::forward<Args>(args)...);
    }
};

template<class F>
FixPoint(F &&) -> FixPoint<std::decay_t<F>>;

}  // namespace alg

#endif
