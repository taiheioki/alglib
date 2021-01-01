#ifndef TEST_GRAPH_EULERIAN_TRAIL_GENERATE_HPP_
#define TEST_GRAPH_EULERIAN_TRAIL_GENERATE_HPP_

#include <random>
#include <vector>

#include "alglib/graph/graph.hpp"

struct Data
{
    int n, m;
    bool is_eulerian;
};

template<class URBG>
alg::DirectedGraph generate_directed(Data data, URBG& engine)
{
    const int n = data.n;
    const int m = data.m;
    alg::DirectedGraph G(n);
    std::uniform_int_distribution dist(0, n - 1);

    if(data.is_eulerian) {
        std::vector<int> tails(m);
        for(int j = 0; j < m; ++j) {
            tails[j] = dist(engine);
        }

        auto heads = tails;
        std::shuffle(heads.begin(), heads.end(), engine);

        alg::DirectedGraph G(n);
        for(int j = 0; j < m; ++j) {
            G.add_edge(tails[j], heads[j]);
        }
    }
    else {
        for(int j = 0; j < m; ++j) {
            G.add_edge(dist(engine), dist(engine));
        }
    }

    return G;
}

#endif
