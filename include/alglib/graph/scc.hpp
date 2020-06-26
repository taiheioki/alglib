#ifndef ALGLIB_GRAPH_SCC_HPP_
#define ALGLIB_GRAPH_SCC_HPP_

#include <algorithm>
#include <stack>
#include <vector>

#include "alglib/graph/graph.hpp"
#include "alglib/graph/topological_sort.hpp"

namespace alg
{
// BEGIN DISPLAY tarjan1972
class SccTarjan
{
public:
    std::vector<std::vector<int>> components;  // components[i] := original vertices of scc_graph[i]

protected:
    const DirectedGraph& G;
    std::vector<int> index;
    int num_visited;
    std::stack<int> S;

    enum
    {
        Unvisited = -1,
        Done      = -2,
    };

    // Find strongly connected components in the DFS tree rooted at u.
    // The return value is the "lowlink" number of u.
    int strong_connect(const int u)
    {
        S.push(u);
        index[u]    = num_visited;
        int lowlink = num_visited;
        ++num_visited;

        for(const auto [v, e] : G.outedges(u)) {
            if(index[v] == Unvisited)
                lowlink = std::min(lowlink, strong_connect(v));
            else if(index[v] != Done)  // v is in S
                lowlink = std::min(lowlink, index[v]);
        }

        if(index[u] == lowlink) {  // u is the root of a strongly connected component
            components.emplace_back();
            for(;;) {
                const int v = S.top();
                S.pop();
                index[v] = Done;
                components.back().push_back(v);
                if(u == v)
                    break;
            }
        }

        return lowlink;
    }

public:
    // Find strongly connected components of G in topological order.
    SccTarjan(const DirectedGraph& G) : G(G), index(G.n_vertices(), Unvisited), num_visited(0)
    {
        for(int u = 0; u < G.n_vertices(); ++u) {
            if(index[u] == Unvisited) {
                strong_connect(u);
            }
        }
        std::reverse(components.begin(), components.end());
    }
};
// END DISPLAY tarjan1972

// BEGIN DISPLAY kosaraju1978
class SccKosaraju
{
public:
    std::vector<std::vector<int>> components;  // components[i] := original vertices of scc_graph[i]

protected:
    const DirectedGraph& G;
    std::vector<bool> visited;

    // Visit "Unvisited" vertices reachable to u on G.
    void reachable_to(const int u)
    {
        visited[u] = true;
        components.back().push_back(u);

        for(const auto [v, e] : G.inedges(u)) {
            if(!visited[v]) {
                reachable_to(v);
            }
        }
    }

public:
    // Find strongly connected components of G in topological order.
    SccKosaraju(const DirectedGraph& G) : G(G), visited(G.n_vertices())
    {
        for(const int u : TopologicalSortTarjan(G).order) {
            if(!visited[u]) {
                components.emplace_back();
                reachable_to(u);
            }
        }
    }
};
// END DISPLAY kosaraju1978
}  // namespace alg

#endif
