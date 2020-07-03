#ifndef TEST_GRAPH_GENERATE_HPP_
#define TEST_GRAPH_GENERATE_HPP_

#include <cassert>
#include <numeric>
#include <random>
#include <vector>

#include "alglib/graph/graph.hpp"

template<class URBG>
alg::UndirectedGraph generate_graph(const int n, const int m, URBG& engine)
{
    alg::UndirectedGraph G(n);
    std::uniform_int_distribution dist(0, n - 1);
    for(int e = 0; e < m; ++e) {
        const int u = dist(engine), v = dist(engine);
        G.add_edge(u, v);
    }
    return G;
}

template<class URBG>
alg::DirectedGraph generate_digraph(const int n, const int m, URBG& engine)
{
    alg::DirectedGraph G(n);
    std::uniform_int_distribution dist(0, n - 1);
    for(int e = 0; e < m; ++e) {
        const int u = dist(engine), v = dist(engine);
        G.add_edge(u, v);
    }
    return G;
}

template<class URBG>
alg::UndirectedGraph generate_bipartite_graph(const int n1, const int n2, const int m, URBG& engine)
{
    alg::UndirectedGraph G(n1 + n2);
    std::uniform_int_distribution dist1(0, n1 - 1), dist2(n1, n1 + n2 - 1);
    for(int e = 0; e < m; ++e) {
        const int u = dist1(engine), v = dist2(engine);
        G.add_edge(u, v);
    }
    return G;
}

template<class URBG>
alg::UndirectedGraph generate_tree(const int n, URBG& engine)
{
    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    std::shuffle(perm.begin(), perm.end(), engine);

    alg::UndirectedGraph G(n);
    for(int i = 1; i < n; ++i) {
        const int u = perm[std::uniform_int_distribution(0, i - 1)(engine)], v = perm[i];
        G.add_edge(u, v);
    }

    return G;
}

template<class URBG>
alg::UndirectedGraph generate_connected_graph(const int n, const int m, URBG& engine)
{
    assert(m >= n - 1);
    auto G = generate_graph(n, m - n + 1, engine);
    auto T = generate_tree(n, engine);
    for(const auto [u, v] : T.edges()) {
        G.add_edge(u, v);
    }
    return G;
}

#endif
