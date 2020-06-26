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

// A tag indicating directed graphs.
struct Directed
{};

// A tag indicating undirected graphs.
struct Undirected
{};

template<class Direction>
class Graph;

using DirectedGraph   = Graph<Directed>;
using UndirectedGraph = Graph<Undirected>;

template<>
class Graph<Directed>
{
protected:
    // Vin[v] := a list of {edge id, adjacent vertex} entering to v
    // Vout[v] := a list of {edge id, adjacent vertex} leaving from v
    std::vector<std::vector<std::pair<int, int>>> Vin, Vout;
    std::vector<Edge> E;

public:
    // Initialize an edgeless digraph with n vetices.
    Graph(const int n = 0) : Vin(n), Vout(n) {}

    // Return the number of vertices.
    int n_vertices() const noexcept { return Vin.size(); }

    // Return the array of {edge id, head} entering to v.
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
        Vin.emplace_back();
        Vout.emplace_back();
    }

    // Add a new edge.
    void add_edge(const int tail, const int head)
    {
        assert(0 <= tail && tail < n_vertices());
        assert(0 <= head && head < n_vertices());
        Vin[head].emplace_back(n_edges(), tail);
        Vout[tail].emplace_back(n_edges(), head);
        E.emplace_back(tail, head);
    }
};

template<>
class Graph<Undirected>
{
protected:
    // V[v] := a list of {edge id, adjacent vertex} adjacent to v
    std::vector<std::vector<std::pair<int, int>>> V;
    std::vector<Edge> E;

public:
    // Initialize an edgeless graph with n vetices.
    Graph(const int n = 0) : V(n) {}

    // Return the number of vertices.
    int n_vertices() const noexcept { return V.size(); }

    // Return the array of {edge id, head} adjacent to v.
    auto& edges(const int u) const { return V[u]; }
    auto& inedges(const int u) const { return V[u]; }
    auto& outedges(const int u) const { return V[u]; }

    // Return the edegree of v.
    int degree(const int u) const { return V[u].size(); }
    int indegree(const int u) const { return degree(u); }
    int outdegree(const int u) const { return degree(u); }

    // Return the array of edges.
    int n_edges() const noexcept { return E.size(); }

    // Return the e-th edge.
    Edge edge(const int e) const { return E[e]; }

    // Return the array of edges.
    auto& edges() const noexcept { return E; }

    // Add a new vertex.
    void add_vertex() { V.emplace_back(); }

    // Add a new edge.
    void add_edge(const int tail, const int head)
    {
        assert(0 <= tail && tail < n_vertices());
        assert(0 <= head && head < n_vertices());
        V[head].emplace_back(n_edges(), tail);
        V[tail].emplace_back(n_edges(), head);
        E.emplace_back(tail, head);
    }
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
DirectedGraph simplify(const DirectedGraph& G)
{
    const int n = G.n_vertices();
    DirectedGraph Gsimp(n);
    std::vector<bool> buckets(n);

    for(int v = 0; v < n; ++v) {
        for(const auto [j, u] : G.outedges(v)) {
            if(v != u && !buckets[u]) {
                buckets[u] = true;
                Gsimp.add_edge(v, u);
            }
        }

        // Initialize buckets for next use. This can be done by restoring only updated buckets.
        for(const auto [j, u] : Gsimp.outedges(v)) {
            buckets[u] = false;
        }
    }

    return Gsimp;
}

}  // end of namespace alg

#endif
