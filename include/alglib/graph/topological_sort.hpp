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
    TopologicalSortKahn(const Graph& G)
    {
        const int n = G.size();

        std::vector<int> indeg(n, 0);
        for(const auto& v : G) {
            for(const Edge& e : v) {
                indeg[e.head]++;
            }
        }

        std::stack<int> S;  // Any other containers are OK
        for(int i = 0; i < n; ++i) {
            if(indeg[i] == 0) {
                S.push(i);
            }
        }

        while(!S.empty()) {
            const int v = S.top();
            S.pop();
            order.push_back(v);
            for(const Edge& e : G[v]) {
                const int u = e.head;
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
    bool is_dag = true;  // Whether there exists a directed cycle reachable from r.

    // order[0], order[1], ... is a pre-topological order of vertices reachable from r.
    std::vector<int> order;

protected:
    enum class Flag
    {
        Unvisited,
        Visiting,
        Visited,
    };
    std::vector<Flag> flags;

    // Recursively traverse vertices that are reachable from v.
    void dfs(const Graph& G, const int v)
    {
        if(flags[v] != Flag::Unvisited)
            return;
        flags[v] = Flag::Visiting;

        for(const Edge& e : G[v]) {
            is_dag &= flags[e.head] != Flag::Visiting;
            dfs(G, e.head);
        }

        flags[v] = Flag::Visited;
        order.push_back(v);
    }

public:
    // Sort pre-topologically vertices of G.
    TopologicalSortTarjan(const Graph& G) : flags(G.size(), Flag::Unvisited)
    {
        for(int i = 0; i < int(G.size()); ++i) {
            dfs(G, i);
        }
        std::reverse(order.begin(), order.end());
    }
};
// END DISPLAY tarjan1976

}  // namespace alg

#endif
