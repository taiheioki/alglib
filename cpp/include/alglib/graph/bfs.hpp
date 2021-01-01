#ifndef ALGLIB_GRAPH_BFS_HPP_
#define ALGLIB_GRAPH_BFS_HPP_

#include <limits>
#include <queue>
#include <vector>

#include "alglib/graph/graph.hpp"
#include "alglib/graph/tree.hpp"

namespace alg
{
// BEGIN DISPLAY graph/bfs
class BFS
{
public:
    Tree shortest_path_tree;  // A shortest path tree rooted at s

    // dist[v] := the distance from s to v or "Unreachable"
    std::vector<int> dist;
    enum
    {
        Unreachable = std::numeric_limits<int>::max(),
    };

    // Ctor -- the main part of the algorithm
    BFS(const DirectedGraph& G, const int s)
      : shortest_path_tree(G.n_vertices(), s), dist(G.n_vertices(), Unreachable)
    {
        std::queue<int> Q;
        Q.push(s);
        dist[s] = 0;

        while(!Q.empty()) {
            const int u = Q.front();
            Q.pop();
            for(const auto [v, e] : G.outedges(u)) {
                if(shortest_path_tree[v].parent == TreeNode::Invalid) {
                    Q.push(v);
                    shortest_path_tree[v].parent = u;
                    shortest_path_tree[u].children.push_back(v);
                    dist[v] = dist[u] + 1;
                }
            }
        }
    }
};
// END DISPLAY graph/bfs

}  // namespace alg

#endif
