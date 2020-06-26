#ifndef ALGLIB_GRAPH_HPP_
#define ALGLIB_GRAPH_HPP_

#include <cassert>
#include <utility>
#include <vector>

namespace alg
{
// BEGIN DISPLAY graph
struct Edge
{
    int tail, head;  // tail --> head

    Edge() = default;
    constexpr Edge(const int tail, const int head) noexcept : tail(tail), head(head) {}
};

// A tag indicating type of graph direction.
enum class Direction
{
    Directed,
    Undirected,
};

template<Direction>
class Graph;

using DirectedGraph   = Graph<Direction::Directed>;
using UndirectedGraph = Graph<Direction::Undirected>;

// Common implementation of directed and undirected graphs
class GraphBase
{
protected:
    using Vertex = std::vector<std::vector<std::pair<int, int>>>;

    Vertex& Vin;   // Vin[v] := a list of {adjacent vertex, edge id} entering to v
    Vertex& Vout;  // Vout[v] := a list of {adjacent vertex, edge id} leaving from v
    std::vector<Edge> E;

    // Initialize a graph.
    GraphBase(Vertex& Vin, Vertex& Vout) : Vin(Vin), Vout(Vout) {}

public:
    // Return the number of vertices.
    int n_vertices() const noexcept { return Vin.size(); }

    // Return the array of {edge id, tail} entering to v.
    auto& inedges(const int u) const { return Vin[u]; }

    // Return the array of {edge id, head} leaving from v.
    auto& outedges(const int u) const { return Vout[u]; }

    // Return the indegree of v.
    int indegree(const int u) const { return Vin[u].size(); }

    // Return the outedegree of v.
    int outdegree(const int u) const { return Vout[u].size(); }

    // Return the array of edges.
    int n_edges() const noexcept { return E.size(); }

    // Return the e-th edge.
    Edge edge(const int e) const { return E[e]; }

    // Return the array of edges.
    auto& edges() const noexcept { return E; }

    // Add a new vertex.
    void add_vertex()
    {
        const int n = n_vertices();  // Vin and Vout might be the same objects
        Vin.resize(n + 1);
        Vout.resize(n + 1);
    }

    // Add a new edge.
    void add_edge(const int tail, const int head)
    {
        assert(0 <= tail && tail < n_vertices());
        assert(0 <= head && head < n_vertices());
        Vin[head].emplace_back(tail, n_edges());
        Vout[tail].emplace_back(head, n_edges());
        E.emplace_back(tail, head);
    }
};

// In case of directed graphs, Vin and Vout are different objects.
template<>
class Graph<Direction::Directed> : public GraphBase
{
protected:
    Vertex Vin, Vout;

public:
    // Initialize an edgeless directed graph with n vertices.
    Graph(const int n = 0) : GraphBase(Vin, Vout), Vin(n), Vout(n) {}
};

// In case of undirected graphs, Vin and Vout are the same objects.
template<>
class Graph<Direction::Undirected> : public GraphBase
{
protected:
    Vertex V;

public:
    // Initialize an edgeless undirected graph with n vertices.
    Graph(const int n = 0) : GraphBase(V, V), V(n) {}

    // Return the array of {edge id, head} adjacent to v.
    auto& edges(const int u) const { return V[u]; }

    // Return the degree of v.
    int degree(const int u) const { return V[u].size(); }
};
// END DISPLAY graph

// Return the reversed graph of G.
// Time Complexity: O(|V| + |E|)
DirectedGraph reverse(const DirectedGraph& G)
{
    DirectedGraph rev(G.n_vertices());
    for(const auto [u, v] : G.edges()) {
        rev.add_edge(v, u);
    }
    return rev;
}

// Return the graph obtained by removing loops and by unifying parallel edges.
// Time complexity: O(|V| + |E|)
// (Thanks to: @latte0119_)
template<Direction Dir>
Graph<Dir> simplify(const Graph<Dir>& G)
{
    const int n = G.n_vertices();
    Graph<Dir> Gsimp(n);
    std::vector<bool> buckets(n);

    for(int u = 0; u < n; ++u) {
        for(const auto [v, e] : G.outedges(u)) {
            if(!buckets[v] && (Dir == Direction::Directed ? u != v : u < v)) {
                buckets[v] = true;
                Gsimp.add_edge(u, v);
            }
        }

        // Reset buckets for next use. This can be done by restoring only updated buckets, which
        // improves time complexity.
        for(const auto [v, e] : Gsimp.outedges(u)) {
            buckets[v] = false;
        }
    }

    return Gsimp;
}

}  // end of namespace alg

#endif
