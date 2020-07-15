#ifndef ALGLIB_GRAPH_GRAPH_HPP_
#define ALGLIB_GRAPH_GRAPH_HPP_

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "alglib/util/fix_point.hpp"

namespace alg
{
// BEGIN DISPLAY graph/edge
struct Edge
{
    int tail, head;  // tail --> head

    Edge() = default;
    constexpr Edge(const int tail, const int head) noexcept : tail(tail), head(head) {}
};
// END DISPLAY graph/edge

// BEGIN DISPLAY graph/graph_declare
// A tag indicating type of graph direction.
enum class Direction
{
    Undirected,
    Directed,
};

template<Direction>
class Graph;

using UndirectedGraph = Graph<Direction::Undirected>;
using DirectedGraph   = Graph<Direction::Directed>;
// END DISPLAY graph/graph_declare

// BEGIN DISPLAY graph/graph_base
// Common implementation of directed and undirected graphs
class GraphBase
{
protected:
    using Vertex = std::vector<std::vector<std::pair<int, int>>>;

    Vertex& Vin;   // Vin[v] := a list of {adjacent vertex, edge id} entering to v
    Vertex& Vout;  // Vout[u] := a list of {adjacent vertex, edge id} leaving from u
    std::vector<Edge> E;

    // Initialize a graph.
    GraphBase(Vertex& Vin, Vertex& Vout) : Vin(Vin), Vout(Vout) {}

public:
    // Return the number of vertices.
    [[nodiscard]] int n_vertices() const noexcept { return Vin.size(); }

    // Return the array of {edge id, tail} entering to v.
    [[nodiscard]] auto& inedges(const int v) const { return Vin[v]; }

    // Return the array of {edge id, head} leaving from u.
    [[nodiscard]] auto& outedges(const int u) const { return Vout[u]; }

    // Return the indegree of v.
    [[nodiscard]] int indegree(const int v) const { return Vin[v].size(); }

    // Return the outedegree of u.
    [[nodiscard]] int outdegree(const int u) const { return Vout[u].size(); }

    // Return the array of edges.
    [[nodiscard]] int n_edges() const noexcept { return E.size(); }

    // Return the e-th edge.
    [[nodiscard]] Edge edge(const int e) const { return E[e]; }

    // Return the array of edges.
    [[nodiscard]] auto& edges() const noexcept { return E; }

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
// END DISPLAY graph/graph_base

// BEGIN DISPLAY graph/undirected_graph
// In case of undirected graphs, Vin and Vout are the same objects.
template<>
class Graph<Direction::Undirected> : public GraphBase
{
protected:
    Vertex V;

public:
    // Initialize an edgeless undirected graph with n vertices.
    explicit Graph(const int n = 0) : GraphBase(V, V), V(n) {}

    // An assignment operator.
    Graph& operator=(const Graph& G)
    {
        V = G.V;
        return *this;
    }

    // Return the array of edges.
    using GraphBase::edges;

    // Return the array of {edge id, head} adjacent to v.
    [[nodiscard]] auto& edges(const int u) const { return V[u]; }

    // Return the degree of v.
    [[nodiscard]] int degree(const int u) const { return V[u].size(); }

    // Generate the complete graph K_n.
    [[nodiscard]] static Graph complete(const int n)
    {
        Graph G(n);
        for(int u = 0; u < n; ++u) {
            for(int v = u + 1; v < n; ++v) {
                G.add_edge(u, v);
            }
        }
        return G;
    }

    // Generate the complete bipartite graph K_{n1,n2}.
    [[nodiscard]] static Graph complete_bipartite(const int n1, const int n2)
    {
        Graph G(n1 + n2);
        for(int u = 0; u < n1; ++u) {
            for(int v = n1; v < n1 + n2; ++v) {
                G.add_edge(u, v);
            }
        }
        return G;
    }

    // Generate the path P_n.
    [[nodiscard]] static Graph path(const int n)
    {
        Graph G(n);
        for(int u = 0; u < n - 1; ++u) {
            G.add_edge(u, u + 1);
        }
        return G;
    }

    // Generate the cycle C_n.
    [[nodiscard]] static Graph cycle(const int n)
    {
        assert(n >= 1);
        auto G = path(n);
        G.add_edge(n - 1, 0);
        return G;
    }

    // Generate the star graph S_n.
    [[nodiscard]] static Graph star(const int n)
    {
        assert(n >= 1);
        return complete_bipartite(1, n - 1);
    }

    // Generate the Petersen graph.
    [[nodiscard]] static Graph petersen()
    {
        Graph G(10);
        for(int i = 0; i < 5; ++i) {
            G.add_edge(i, i + 5);
            G.add_edge(i, (i + 1) % 5);
            G.add_edge(i + 5, (i + 2) % 5 + 5);
        }
        return G;
    }
};
// END DISPLAY graph/undirected_graph

// In case of directed graphs, Vin and Vout are different objects.
template<>
class Graph<Direction::Directed> : public GraphBase
{
protected:
    Vertex Vin, Vout;

public:
    // Initialize an edgeless directed graph with n vertices.
    explicit Graph(const int n = 0) : GraphBase(Vin, Vout), Vin(n), Vout(n) {}

    // An assignment operator.
    Graph& operator=(const Graph& G)
    {
        Vin  = G.Vin;
        Vout = G.Vout;
        return *this;
    }

    // Generate the directed complete graph.
    [[nodiscard]] static Graph complete(const int n)
    {
        Graph G(n);
        for(int u = 0; u < n; ++u) {
            for(int v = u + 1; v < n; ++v) {
                G.add_edge(u, v);
                G.add_edge(v, u);
            }
        }
        return G;
    }

    // Generate the directed path P_n.
    [[nodiscard]] static Graph path(const int n)
    {
        Graph G(n);
        for(int u = 0; u < n - 1; ++u) {
            G.add_edge(u, u + 1);
        }
        return G;
    }

    // Generate the directed cycle C_n.
    [[nodiscard]] static Graph cycle(const int n)
    {
        auto G = path(n);
        G.add_edge(n - 1, 0);
        return G;
    }
};
// END DISPLAY graph

// Return the undirected graph obtained by ignoreing edge orientations of G.
// Time Complexity: O(|V| + |E|)
[[nodiscard]] UndirectedGraph ignore_orientation(const DirectedGraph& G)
{
    UndirectedGraph H(G.n_vertices());
    for(const auto [u, v] : H.edges()) {
        H.add_edge(u, v);
    }
    return H;
}

// Return the reversed graph of G.
// Time Complexity: O(|V| + |E|)
[[nodiscard]] DirectedGraph reverse(const DirectedGraph& G)
{
    DirectedGraph H(G.n_vertices());
    for(const auto [u, v] : G.edges()) {
        H.add_edge(v, u);
    }
    return H;
}

// Return the graph obtained by removing loops and by unifying parallel edges.
// Time complexity: O(|V| + |E|)
template<Direction Dir>
[[nodiscard]] Graph<Dir> simplify(const Graph<Dir>& G)
{
    const int n = G.n_vertices();
    Graph<Dir> H(n);
    std::vector<bool> buckets(n);

    for(int u = 0; u < n; ++u) {
        for(const auto [v, e] : G.outedges(u)) {
            if(!buckets[v] && (Dir == Direction::Directed ? u != v : u < v)) {
                buckets[v] = true;
                H.add_edge(u, v);
            }
        }

        // Reset buckets for next use. This can be done by restoring only updated buckets, which
        // improves time complexity.
        for(const auto [v, e] : H.outedges(u)) {
            buckets[v] = false;
        }
    }

    return H;
}

// Return the union of G1 and G2.
// Time complexity: O(|V1| + |E1| + |V2| + |E2|)
template<Direction Dir>
[[nodiscard]] Graph<Dir> unite(const Graph<Dir>& G1, const Graph<Dir>& G2)
{
    const int n1 = G1.n_vertices();
    Graph<Dir> H(n1 + G2.n_vertices());

    for(const auto [u, v] : G1.edges()) {
        H.add_edge(u, v);
    }
    for(const auto [u, v] : G2.edges()) {
        H.add_edge(u + n1, v + n1);
    }

    return H;
}

// Check whether G is connected.
// Time Complexity: O(|V| + |E|)
[[nodiscard]] bool is_connected(const UndirectedGraph& G)
{
    if(G.n_vertices() == 0)
        return false;  // The null graph is disconnected

    std::vector<bool> visited(G.n_vertices());

    FixPoint([&](const auto dfs, const int u) -> void {
        visited[u] = true;
        for(const auto [v, e] : G.edges(u)) {
            if(!visited[v])
                dfs(v);
        }
    })(0);

    return std::find(visited.begin(), visited.end(), false) == visited.end();
}

// Check whether G is strongly connected.
// Time Complexity: O(|V| + |E|)
[[nodiscard]] bool is_strongly_connected(const DirectedGraph& G)
{
    if(G.n_vertices() == 0)
        return false;  // The null graph is not strongly connected

    // Check whether all vertices are reachble from 0
    std::vector<bool> visited(G.n_vertices());
    FixPoint([&](const auto dfs, const int u) -> void {
        visited[u] = true;
        for(const auto [v, e] : G.outedges(u)) {
            if(!visited[v])
                dfs(v);
        }
    })(0);

    if(std::find(visited.begin(), visited.end(), false) != visited.end())
        return false;

    // Check whether all vertices are reachble to 0
    std::fill(visited.begin(), visited.end(), false);
    FixPoint([&](const auto dfs, const int v) -> void {
        visited[v] = true;
        for(const auto [u, e] : G.inedges(v)) {
            if(!visited[u])
                dfs(u);
        }
    })(0);

    return std::find(visited.begin(), visited.end(), false) == visited.end();
}

// Check whether G has a cycle.
// Time Complexity: O(|V| + |E|)
[[nodiscard]] bool has_cycle(const UndirectedGraph& G)
{
    const int n = G.n_vertices();
    std::vector<bool> visited(n);

    const auto dfs = FixPoint([&](const auto dfs, const int u, const int parent_edge) -> bool {
        visited[u] = true;
        for(const auto [v, e] : G.edges(u)) {
            if(e != parent_edge && (!visited[v] || dfs(v, e)))
                return true;
        }
        return false;
    });

    for(int u = 0; u < n; ++u) {
        if(!visited[u] && dfs(u, -1))
            return true;
    }

    return false;
}

// Check whether G has a directed cycle.
// Time Complexity: O(|V| + |E|)
[[nodiscard]] bool has_cycle(const DirectedGraph& G)
{
    enum class Flag
    {
        Unvisited,
        Visiting,
        Visited,
    };
    const int n = G.n_vertices();
    std::vector<Flag> flags(n);

    const auto dfs = FixPoint([&](const auto dfs, const int u) -> bool {
        if(flags[u] != Flag::Unvisited)
            return flags[u] == Flag::Visiting;
        flags[u] = Flag::Visiting;

        for(const auto [v, e] : G.outedges(u)) {
            if(dfs(v)) {
                flags[u] = Flag::Visited;
                return true;
            }
        }

        flags[u] = Flag::Visited;
        return false;
    });

    for(int u = 0; u < n; ++u) {
        if(dfs(u))
            return true;
    }

    return false;
}

// Check whether G is a forest.
// Time Complexity: O(|V| + |E|)
[[nodiscard]] bool is_forest(const UndirectedGraph& G)
{
    return !has_cycle(G);
}

// Check whether G is a tree.
// Time Complexity: O(|V| + |E|)
[[nodiscard]] bool is_tree(const UndirectedGraph& G)
{
    return is_connected(G) && is_forest(G);
}

// Check whether G is a directed acyclic graph (DAG).
// Time Complexity: O(|V| + |E|)
[[nodiscard]] bool is_dag(const DirectedGraph& G)
{
    return !has_cycle(G);
}

// Check whether G is simple.
// Time Complexity: O(|V| + |E|)
template<Direction Dir>
[[nodiscard]] bool is_simple(const Graph<Dir>& G)
{
    const int n = G.n_vertices();
    std::vector<bool> buckets(n);

    for(int u = 0; u < n; ++u) {
        for(const auto [v, e] : G.outedges(u)) {
            if(!buckets[v] && u != v)
                buckets[v] = true;
            else
                return false;
        }

        for(const auto [v, e] : G.outedges(u)) {
            buckets[v] = false;
        }
    }

    return true;
}

}  // end of namespace alg

#endif
