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
    std::vector<int> outdeg;  // outdeg[v] := the out-degree of v in the remaining graph.

    void visit(const int v)
    {
        while(outdeg[v] > 0) {
            --outdeg[v];  // Virturally pop the edge by decreasing outdeg[v]
            const auto [j, u] = G.outedges(v)[outdeg[v]];
            visit(u);
            trail.push_back(j);
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
        for(int v = 0; v < G.n_vertices(); ++v) {
            outdeg[v] = G.outdegree(v);
            if(G.indegree(v) < outdeg[v]) {
                result = Result::SemiEulerian;
                s      = v;
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
