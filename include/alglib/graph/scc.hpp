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

    // Find strongly connected components in the DFS tree rooted at v.
    // The return value is the "lowlink" number of v.
    int strong_connect(const int v)
    {
        S.push(v);
        index[v]    = num_visited;
        int lowlink = num_visited;
        ++num_visited;

        for(const auto [j, u] : G.outedges(v)) {
            if(index[u] == Unvisited)
                lowlink = std::min(lowlink, strong_connect(u));
            else if(index[u] != Done)  // u is in S
                lowlink = std::min(lowlink, index[u]);
        }

        if(index[v] == lowlink) {  // v is the root of a strongly connected component
            components.emplace_back();
            for(;;) {
                const int u = S.top();
                S.pop();
                index[u] = Done;
                components.back().push_back(u);
                if(u == v)
                    break;
            }
        }

        return lowlink;
    }

public:
    SccTarjan(const DirectedGraph& G) : G(G), index(G.num_vertices(), Unvisited), num_visited(0)
    {
        for(int v = 0; v < G.num_vertices(); ++v) {
            if(index[v] == Unvisited) {
                strong_connect(v);
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

    // Visit "Unvisited" vertices of G reachable to v.
    void reachable_to(const int v)
    {
        visited[v] = true;
        components.back().push_back(v);

        for(const auto [j, u] : G.inedges(v)) {
            if(!visited[u]) {
                reachable_to(u);
            }
        }
    }

public:
    SccKosaraju(const DirectedGraph& G) : G(G), visited(G.num_vertices())
    {
        for(const int v : TopologicalSortTarjan(G).order) {
            if(!visited[v]) {
                components.emplace_back();
                reachable_to(v);
            }
        }
    }
};
// END DISPLAY kosaraju1978
}  // namespace alg

#endif
