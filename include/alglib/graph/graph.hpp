#ifndef ALGLIB_GRAPH_HPP_
#define ALGLIB_GRAPH_HPP_

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

class DirectedGraph
{
protected:
    // m_inedges[v] := a list of {edge id, adjacent vertex} entering to v
    std::vector<std::vector<std::pair<int, int>>> m_inedges, m_outedges;
    std::vector<Edge> E;

public:
    // Initialize an empty digraph.
    DirectedGraph() = default;

    // Initialize an edgeless digraph with n vetices.
    DirectedGraph(const int n) : m_inedges(n), m_outedges(n) {}

    // Return the number of vertices.
    int num_vertices() const noexcept { return m_inedges.size(); }

    // Return the array of {edge id, tail} whose heads are v.
    auto& inedges(const int v) const { return m_inedges[v]; }

    // Return the indegree of v.
    int indegree(const int v) const { return inedges(v).size(); }

    // Return the array of {edge id, head} whose tails are v.
    auto& outedges(const int v) const { return m_outedges[v]; }

    // Return the outedegree of v.
    int outdegree(const int v) const { return outedges(v).size(); }

    // Return the j-th edge.
    Edge edge(const int j) const { return E[j]; }

    // Return the array of edges.
    auto& edges() const noexcept { return E; }

    // Return the array of edges.
    int num_edges() const noexcept { return E.size(); }

    // Add a new vertex.
    void add_vertex()
    {
        m_inedges.emplace_back();
        m_outedges.emplace_back();
    }

    // Add a new edge.
    void add_edge(const int tail, const int head)
    {
        assert(0 <= tail && tail < num_vertices());
        assert(0 <= head && head < num_vertices());
        const int j = num_edges();
        E.emplace_back(tail, head);
        m_inedges[head].emplace_back(j, tail);
        m_outedges[tail].emplace_back(j, head);
    }
    void add_edge(const Edge e) { add_edge(e.tail, e.head); }
};

// Return the reversed graph.
// Time complexity: O(|V| + |E|)
DirectedGraph reverse(const DirectedGraph& G)
{
    DirectedGraph Grev(G.num_vertices());
    for(const Edge e : G.edges()) {
        Grev.add_edge(e.head, e.tail);
    }
    return Grev;
}
// END DISPLAY graph

}  // end of namespace alg

#endif
