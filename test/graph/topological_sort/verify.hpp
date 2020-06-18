#ifndef TEST_GRAPH_TOPOLOGICAL_SORT_VERIFY_HPP_
#define TEST_GRAPH_TOPOLOGICAL_SORT_VERIFY_HPP_

#include <cassert>

#include "alglib/graph/graph.hpp"

template<typename TopologicalSort>
void verify(const alg::Graph& G, const TopologicalSort& top)
{
    if(top.is_dag) {
        // Check of topological ordering
        const int n = G.size();
        assert(int(top.order.size()) == n);

        std::vector<int> inv(n);
        for(int i = 0; i < n; ++i) {
            assert(0 <= top.order[i] && top.order[i] <= n);
            inv[top.order[i]] = i;
        }
        for(const int v : top.order) {
            for(const alg::Edge& e : G[v]) {
                assert(inv[e.tail] < inv[e.head]);
            }
        }
    }
    else {
        // TODO: check of pre-topological ordering
    }
}

#endif
