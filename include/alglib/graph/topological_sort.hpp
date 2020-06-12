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
    std::vector<int> order;  // Represent a topological order if is_dag = true.

    // Test if G is a DAG, and if so, sort vertices of G topologically.
    TopologicalSortKahn(const Graph& G)
    {
        const int n = G.size();

        std::vector<int> indeg(n, 0);
        for(int i = 0; i < n; ++i) {
            for(const Edge& e : G[i]) {
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
    enum
    {
        All = -1
    };

    bool is_dag = true;      // Whether there exists a cycle reachable from r.
    std::vector<int> order;  // A pre-topological order or vertices reachable from r.

protected:
    enum class Flag
    {
        Unvisited,
        Visiting,
        Visited,
    };
    std::vector<Flag> flags;

    // Recursively traverse vertices that are reachable from r.
    void dfs(const Graph& G, const int r)
    {
        flags[r] = Flag::Visiting;

        for(const Edge& e : G[r]) {
            const int u = e.head;
            is_dag &= flags[u] != Flag::Visiting;
            if(flags[u] != Flag::Visited)
                dfs(G, u);
        }

        flags[r] = Flag::Visited;
        order.push_back(r);
    }

public:
    // Sort pre-topologically vertices of G that are reachable from r.
    // If r is "All", all vertices are targets.
    TopologicalSortTarjan(const Graph& G, const int r = All) : flags(G.size(), Flag::Unvisited)
    {
        if(r == All) {
            for(int i = 0; i < int(G.size()); ++i) {
                dfs(G, i);
            }
        }
        else {
            dfs(G, r);
        }
        std::reverse(order.begin(), order.end());
    }
};
// END DISPLAY tarjan1976

}  // namespace alg

#endif
