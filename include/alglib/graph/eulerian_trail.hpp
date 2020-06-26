#ifndef ALGLIB_GRAPH_EULERIAN_TRAIL_HPP_
#define ALGLIB_GRAPH_EULERIAN_TRAIL_HPP_

#include <algorithm>
#include <vector>

#include "alglib/graph/graph.hpp"

namespace alg
{
// BEGIN DISPLAY hierholzer1873
class EulerianTrailHierholzer
{
private:
    const DirectedGraph& G;
    std::vector<int> outdeg;  // outdeg[u] := the out-degree of u in the remaining graph.

    void visit(const int u)
    {
        while(outdeg[u] > 0) {
            --outdeg[u];  // Virturally pop the edge by decreasing outdeg[v]
            const auto [v, e] = G.outedges(u)[outdeg[u]];
            visit(v);
            trail.push_back(e);
        }
    }

public:
    // Array of edges representing an Eulerian tour if G is Eulerian and an Eulerian trail if G is
    // semi-Eulerian.
    std::vector<int> trail;

    // Whether G is Eulerian, semi-Eulerian, or neither.
    enum class Result
    {
        Eulerian,
        SemiEulerian,
        None,
    } result = Result::Eulerian;

    // Find an Eulerian tour if G is Eulerian and an Eulerian trail if G is semi-Eulerian.
    EulerianTrailHierholzer(const DirectedGraph& G) : G(G), outdeg(G.n_vertices())
    {
        if(G.n_vertices() == 0)
            return;  // The empty graph is Eulerian

        // Search for a starting point
        int s = 0;
        for(int u = 0; u < G.n_vertices(); ++u) {
            outdeg[u] = G.outdegree(u);
            if(G.indegree(u) < outdeg[u]) {
                result = Result::SemiEulerian;
                s      = u;
            }
        }

        visit(s);

        if(int(trail.size()) < G.n_edges()) {
            trail.clear();
            result = Result::None;
        }
        else {
            std::reverse(trail.begin(), trail.end());
        }
    }
};
// END DISPLAY hierholzer1873

}  // namespace alg

#endif
