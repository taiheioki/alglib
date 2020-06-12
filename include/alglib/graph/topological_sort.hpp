#ifndef ALGLIB_GRAPH_TOPOLOGICAL_SORT_HPP_
#define ALGLIB_GRAPH_TOPOLOGICAL_SORT_HPP_

#include <numeric>
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

    // Ctor -- the main part of the algorithm
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
    bool is_dag;             // Whether the input is a DAG or not.
    std::vector<int> order;  // A pre-topological order.

    // Ctor -- the main part of the algorithm
    TopologicalSortTarjan(const Graph& G) {}
};
// END DISPLAY tarjan1976

}  // namespace alg

#endif
