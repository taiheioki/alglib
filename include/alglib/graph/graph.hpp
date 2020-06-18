#ifndef ALGLIB_GRAPH_HPP_
#define ALGLIB_GRAPH_HPP_

#include <cassert>
#include <cstddef>
#include <tuple>
#include <utility>
#include <vector>

namespace alg
{
// BEGIN DISPLAY graph

// Classes for bases objects: vertices and edges
struct Vertex
{
    const int id;
    constexpr Vertex(const int id) noexcept : id(id) {}
};

template<class VertexType = Vertex>
class Edge
{
public:
    using Vertex = VertexType;

protected:
    Vertex &m_tail, &m_head;  // tail -> head

public:
    constexpr Edge(Vertex& tail, Vertex& head) noexcept : m_tail(tail), m_head(head) {}

    // Accessors
    constexpr Vertex& tail() noexcept { return m_tail; }
    constexpr const Vertex& tail() const noexcept { return m_tail; }
    constexpr Vertex& head() noexcept { return m_head; }
    constexpr const Vertex& head() const noexcept { return m_head; }

    // For structured bindings
    /*
    template<std::size_t I>
    constexpr Vertex& get() noexcept
    {
        return I == 0 ? tail() : head();
    }
    */

    template<std::size_t I>
    constexpr const Vertex& get() const noexcept
    {
        return I == 0 ? tail() : head();
    }
};

}  // namespace alg

// For structured bindings of alg::Edge<VertexType>
namespace std
{
template<class VertexType>
struct tuple_size<alg::Edge<VertexType>> : integral_constant<size_t, 2>
{};

template<size_t I, class VertexType>
struct tuple_element<I, alg::Edge<VertexType>>
{
    using type = VertexType;
};

}  // namespace std

namespace alg
{
// For range-based for
template<class Iterator>
class Range
{
private:
    const Iterator m_begin, m_end;
    const int m_size;

public:
    template<typename Container>
    constexpr Range(Container& container)
      : Range(container.begin(), container.end(), container.size())
    {}
    constexpr Range(Iterator&& begin, Iterator&& end, const int size) noexcept
      : m_begin(begin), m_end(end), m_size(size)
    {}

    constexpr Iterator begin() const noexcept { return m_begin; }
    constexpr Iterator end() const noexcept { return m_end; }
    constexpr int size() const noexcept { return m_size; }
};

template<typename Container>
Range(Container& container) -> Range<decltype(container.begin())>;  // Deduction guide

// Main
template<class VertexType = Vertex, class EdgeType = Edge<VertexType>>
class Graph
{
public:
    using Vertex = VertexType;
    using Edge   = EdgeType;

protected:
    std::vector<Vertex> V;
    std::vector<std::vector<Edge>> E;  // E[v] := edges from v

public:
    // Initialize an empty graph.
    // Time complexity: O(1)
    Graph() = default;

    // Initialize an edgeless graph with n vetices.
    // Time complexity: O(n)
    Graph(const int n) : E(n)
    {
        V.reserve(n);  // Pre-allocate memory for performance
        for(int i = 0; i < n; ++i) {
            V.emplace_back(i);
        }
    }

    // Access the id-th vertex.
    // Time complexity: O(1)
    Vertex& vertex(const int id) { return V[id]; }
    const Vertex& vertex(const int id) const { return V[id]; }

    // Return a range of vertices.
    // Time complexity: O(1)
    auto vertices() noexcept { return Range(V); }
    auto vertices() const noexcept { return Range(V); }

    // Access the outgoing edges from the id-th vertex.
    // Time complexity: O(1)
    auto outedges(const int id) noexcept { return Range(E[id]); }
    auto outedges(const int id) const noexcept { return Range(E[id]); }

    // Add a new vertex by in-place construction.
    // Time complexity: amortized O(1)
    template<typename... Args>
    void add_vertex(Args&&... args)
    {
        V.emplace_back(vertices().size(), std::forward<Args>(args)...);
        E.emplace_back();
    }

    // Add a new vertex by in-place construction.
    // Time complexity: amortized O(1)
    template<typename... Args>
    void add_edge(const int tail, const int head, Args&&... args)
    {
        assert(0 <= tail && tail < vertices().size());
        assert(0 <= head && head < vertices().size());
        E[tail].emplace_back(V[tail], V[head], std::forward<Args>(args)...);
    }
};

// Return the reversed edge.
// Time complexity: O(1)
template<typename Edge>
Edge reverse(const Edge& e)
{
    Edge erev = e;
    std::swap(erev.tail, erev.head);
    return erev;
}

// Return the reversed graph.
// Time complexity: O(|V| + |E|)
template<typename Vertex, typename Edge>
Graph<Vertex, Edge> reverse(const Graph<Vertex, Edge>& G)
{
    Graph<Vertex, Edge> Grev(G.vertices().size());
    for(const Edge& e : G.edges()) {
        Grev.add_edge(e.reverse());
    }
    return Grev;
}
// END DISPLAY graph

}  // end of namespace alg

#endif
