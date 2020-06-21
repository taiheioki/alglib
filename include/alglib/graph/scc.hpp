#ifndef ALGLIB_GRAPH_SCC_HPP_
#define ALGLIB_GRAPH_SCC_HPP_

#include <vector>

#include "alglib/graph/graph.hpp"
#include "alglib/graph/topological_sort.hpp"

namespace alg
{
// BEGIN DISPLAY kosaraju1978
class SccKosaraju
{
public:
    DirectedGraph scc_graph;                   // A graph which is obtained by contracting each scc
    std::vector<std::vector<int>> components;  // components[i] := original vertices of scc_graph[i]
    std::vector<int> component_ids;            // components[component_ids[v]] contains v

protected:
    enum
    {
        Unvisited = -1,
    };

    // Visit "Unvisited" vertices of G reachable to v.
    void reachable_to(const DirectedGraph& G, const int v)
    {
        if(component_ids[v] != Unvisited)
            return;

        const int scc_id = scc_graph.num_vertices() - 1;
        component_ids[v] = scc_id;
        components[scc_id].push_back(v);

        for(const auto [j, u] : G.inedges(v)) {
            reachable_to(G, u);
            scc_graph.add_edge(component_ids[u], scc_id);
        }
    }

public:
    SccKosaraju(const DirectedGraph& G) : component_ids(G.num_vertices(), Unvisited)
    {
        for(const int v : TopologicalSortTarjan(G).order) {
            if(component_ids[v] == Unvisited) {
                scc_graph.add_vertex();
                components.emplace_back();
                reachable_to(G, v);
            }
        }

        scc_graph = simplify(scc_graph);
    }
};
// END DISPLAY kosaraju1978
}  // namespace alg

#endif
