#ifndef ALGLIB_GRAPH_HPP_
#define ALGLIB_GRAPH_HPP_

#include <vector>

namespace alg
{

struct Edge
{
    int src; // tail
    int dst; // head
};

using Graph = std::vector<std::vector<Edge>>;

} // end of namespace alg

#endif
