#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=10000"

#include <iostream>
#include <random>

#include "../generate.hpp"
#include "alglib/graph/graph.hpp"

using namespace std;
using namespace alg;

mt19937 engine;

void test(const DirectedGraph& G, bool ans)
{
    static int ncase = 0;
    cerr << "Case #" << ++ncase << endl;
    assert(is_strongly_connected(shuffle_vertices(G, engine)) == ans);
}

int main()
{
    test(DirectedGraph(0), false);
    test(DirectedGraph(1), true);
    test(DirectedGraph(100000), false);
    test(DirectedGraph::path(100000), false);
    test(DirectedGraph::cycle(1), true);
    test(DirectedGraph::cycle(2), true);
    test(DirectedGraph::cycle(100000), true);

    const auto K300 = DirectedGraph::complete(300);
    test(K300, true);
    test(unite(K300, DirectedGraph(1)), false);

    auto G = unite(K300, K300);
    test(G, false);
    G.add_edge(0, 300);
    test(G, false);
    G.add_edge(599, 299);
    test(G, true);

    cout << "Hello World" << endl;
}
