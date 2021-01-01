#ifndef TEST_GRAPH_EULERIAN_TRAIL_VERIFY_HPP_
#define TEST_GRAPH_EULERIAN_TRAIL_VERIFY_HPP_

#include <algorithm>
#include <cassert>
#include <vector>

#include "alglib/graph/eulerian_trail.hpp"
#include "alglib/graph/graph.hpp"

template<class EulerianTrail>
void verify(const alg::DirectedGraph& G, const EulerianTrail& euler)
{
    using Result = alg::EulerianTrailHierholzer::Result;
    const int m  = G.n_edges();

    if(euler.result == Result::Eulerian) {
        assert(int(euler.trail.size()) == m);

        std::vector<bool> used(m);
        for(int i = 0; i < m; ++i) {
            assert(!used[euler.trail[i]]);
            assert(G.edge(euler.trail[i]).head == G.edge(euler.trail[(i + 1) % m]).tail);
            used[euler.trail[i]] = true;
        }

        assert(std::find(used.begin(), used.end(), false) == used.end());
    }
    else if(euler.result == Result::None) {
    }
}

#endif
