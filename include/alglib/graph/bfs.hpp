#ifndef ALGLIB_GRAPH_BFS_HPP_
#define ALGLIB_GRAPH_BFS_HPP_

#include <algorithm>
#include <queue>
#include <vector>

#include "graph.hpp"

namespace alg
{
class BFS
{
protected:
    std::vector<int> prev;  // prev[v] := the parent of v in a BFS tree

public:
    enum
    {
        Unvisited = -1,
        Source    = -2
    };

    BFS(const Graph& G, const int s) : prev(G.size(), Unvisited)
    {
        std::queue<int> Q;
        Q.push(s);
        prev[s] = Source;

        while(!Q.empty()) {
            const int v = Q.front();
            Q.pop();
            for(const Edge& e : G[v]) {
                if(prev[e.dst] == Unvisited) {
                    Q.push(e.dst);
                    prev[e.dst] = v;
                }
            }
        }
    }

    // Build a shortest path from s to t.
    // If G has no s--t path, return an empty array.
    std::vector<int> path_to(const int t)
    {
        std::vector<int> P;
        if(prev[t] != Unvisited) {
            for(int v = t; v != Source; v = prev[v]) {
                P.push_back(v);
            }
            std::reverse(P.begin(), P.end());
        }
        return P;
    }
};

}  // end of namespace alg

#endif
