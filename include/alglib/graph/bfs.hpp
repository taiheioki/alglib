#ifndef ALGLIB_GRAPH_BFS_HPP_
#define ALGLIB_GRAPH_BFS_HPP_

#include <climits>
#include <queue>
#include <vector>

#include "alglib/graph/graph.hpp"
#include "alglib/graph/tree.hpp"

namespace alg
{
// BEGIN DISPLAY graph/bfs
class BFS
{
protected:
    Tree T;                 // A shortest path tree rooted at s
    std::vector<int> dist;  // dist[v] := the distance from s to v or "Unreachable"

public:
    enum
    {
        Unreachable = INT_MAX
    };

    // Ctor -- the main part of the algorithm
    BFS(const Graph& G, const int s) : T(G.size(), s), dist(G.size(), Unreachable)
    {
        std::queue<int> Q;
        Q.push(s);
        dist[s] = 0;

        while(!Q.empty()) {
            const int v = Q.front();
            Q.pop();
            for(const Edge& e : G[v]) {
                if(T[e.head].parent == TreeNode::Invalid) {
                    Q.push(e.head);
                    T[e.head].parent = v;
                    T[v].children.push_back(e.head);
                    dist[e.head] = dist[v] + 1;
                }
            }
        }
    }

    // Return a shortest path tree rooted at s.
    Tree shortest_path_tree() const
    {
        return T;
    }

    // Return the array of shortest path lengths from s to each vertex.
    std::vector<int> distance_list() const
    {
        return dist;
    }
};
// END DISPLAY graph/bfs

}  // namespace alg

#endif
