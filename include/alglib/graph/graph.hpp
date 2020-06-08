#ifndef ALGLIB_GRAPH_HPP_
#define ALGLIB_GRAPH_HPP_

#include <vector>

namespace alg
{
// BEGIN DISPLAY graph
struct Edge
{
    int tail;
    int head;

    Edge() = default;
    constexpr Edge(const int tail, const int head) noexcept
      : tail(tail), head(head)
    {}
};

using Graph = std::vector<std::vector<Edge>>;
// END DISPLAY graph

}  // end of namespace alg

#endif
