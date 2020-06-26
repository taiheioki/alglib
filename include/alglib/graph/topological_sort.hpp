#ifndef ALGLIB_GRAPH_TOPOLOGICAL_SORT_HPP_
#define ALGLIB_GRAPH_TOPOLOGICAL_SORT_HPP_

#include <algorithm>
#include <stack>
#include <vector>

#include "alglib/graph/graph.hpp"

namespace alg
{
// BEGIN DISPLAY kahn1962
class TopologicalSortKahn
{
public:
    bool is_dag;             // Whether the input is a DAG or not.
    std::vector<int> order;  // If is_dag = true, order[0], order[1], ... is a topological order.

    // Test if G is a DAG, and if so, sort vertices of G topologically.
    TopologicalSortKahn(const DirectedGraph& G)
    {
        const int n = G.n_vertices();
        std::vector<int> indeg(n);
        std::stack<int> S;  // Any other containers are OK

        for(int v = 0; v < n; ++v) {
            indeg[v] = G.indegree(v);
            if(indeg[v] == 0) {
                S.push(v);
            }
        }

        while(!S.empty()) {
            const int v = S.top();
            S.pop();
            order.push_back(v);
            for(const auto [j, u] : G.outedges(v)) {
                indeg[u]--;
                if(indeg[u] == 0) {
                    S.push(u);
                }
            }
        }

        is_dag = int(order.size()) == n;
    }
};
// END DISPLAY kahn1962

// BEGIN DISPLAY tarjan1976
class TopologicalSortTarjan
{
public:
    bool is_dag = true;      // Whether there exists a directed cycle.
    std::vector<int> order;  // order[0], order[1], ... is a pre-topological order of vertices.

protected:
    const DirectedGraph& G;

    enum class Flag
    {
        Unvisited,
        Visiting,
        Visited,
    };
    std::vector<Flag> flags;

    // Recursively traverse vertices that are reachable from v.
    void dfs(const int v)
    {
        if(flags[v] != Flag::Unvisited)
            return;
        flags[v] = Flag::Visiting;

        for(const auto [j, u] : G.outedges(v)) {
            is_dag &= flags[u] != Flag::Visiting;
            dfs(u);
        }

        flags[v] = Flag::Visited;
        order.push_back(v);
    }

public:
    // Sort pre-topologically vertices of G.
    TopologicalSortTarjan(const DirectedGraph& G) : G(G), flags(G.n_vertices(), Flag::Unvisited)
    {
        for(int v = 0; v < G.n_vertices(); ++v) {
            dfs(v);
        }
        std::reverse(order.begin(), order.end());
    }
};
// END DISPLAY tarjan1976

}  // namespace alg

#endif
