#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=10000"

#include <iostream>
#include <random>

#include "../generate.hpp"
#include "alglib/graph/graph.hpp"

using namespace std;
using namespace alg;

mt19937 engine;

template<Direction Dir>
void test(const Graph<Dir>& G, bool ans)
{
    static int ncase = 0;
    cerr << "Case #" << ++ncase << endl;
    assert(is_simple(shuffle_vertices(G, engine)) == ans);
}

int main()
{
    test(UndirectedGraph(0), true);
    test(UndirectedGraph(1), true);
    test(UndirectedGraph(100000), true);
    test(UndirectedGraph::petersen(), true);
    test(UndirectedGraph::path(100000), true);
    test(UndirectedGraph::cycle(1), false);
    test(UndirectedGraph::cycle(2), false);
    test(UndirectedGraph::cycle(100000), true);
    test(UndirectedGraph::star(100000), true);
    test(UndirectedGraph::complete(300), true);
    test(UndirectedGraph::complete_bipartite(300, 300), true);

    auto T = generate_tree(100000, engine);
    test(T, true);
    T.add_edge(0, 1);
    T.add_edge(0, 1);
    test(T, false);

    T = generate_tree(100000, engine);
    T.add_edge(9999, 9999);
    test(T, false);

    test(generate_graph(100, 10000, engine), false);
    test(generate_graph(300, 300 * 299 / 2 + 1, engine), false);

    test(DirectedGraph(0), true);
    test(DirectedGraph(1), true);
    test(DirectedGraph(100000), true);
    test(DirectedGraph::cycle(1), false);
    test(DirectedGraph::cycle(2), true);
    test(DirectedGraph::complete(300), true);

    auto C = DirectedGraph::cycle(100000);
    test(C, true);
    C.add_edge(0, 1);
    test(C, false);

    auto P = DirectedGraph::path(100000);
    P.add_edge(9999, 9999);
    test(P, false);

    test(generate_digraph(300, 300 * 299 + 1, engine), false);

    cout << "Hello World" << endl;
}
