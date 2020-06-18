#ifndef ALGLIB_GRAPH_SCC_HPP_
#define ALGLIB_GRAPH_SCC_HPP_

#include <vector>
#include "alglib/graph/graph.hpp"
#include "alglib/graph/topological_sort.hpp"

namespace alg
{
// BEGIN DISPLAY kosaraju
class SccKosaraju
{
public:
    Graph scc_graph;                           // A graph which is obtained by contracting each scc
    std::vector<std::vector<int>> components;  // components[i] := original vertices of scc_graph[i]
    std::vector<int> component_ids;            // components[component_ids[v]] contains v

    SccKosaraju(const Graph& G)
    {
        const auto top_order = TopologicalSortTarjan(G).order;
        const Graph Grev     = reverse(G);

        for(const int v : top_order) {
            Grev[v]
        }
    }
};
// END DISPLAY kosaraju
}  // namespace alg

#endif
