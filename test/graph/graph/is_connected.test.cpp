#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=10000"

#include <iostream>
#include <random>

#include "../generate.hpp"
#include "alglib/graph/graph.hpp"

using namespace std;
using namespace alg;

void test(const UndirectedGraph& G, bool ans)
{
    static int ncase = 0;
    cerr << "Case #" << ++ncase << endl;
    assert(is_connected(G) == ans);
}

int main()
{
    test(UndirectedGraph(0), false);
    test(UndirectedGraph(1), true);
    test(UndirectedGraph(100000), false);
    test(UndirectedGraph::petersen(), true);
    test(UndirectedGraph::path(100000), true);
    test(UndirectedGraph::cycle(100000), true);
    test(UndirectedGraph::star(100000), true);
    test(UndirectedGraph::complete_bipartite(300, 300), true);

    const auto K300 = UndirectedGraph::complete(300);
    test(K300, true);
    test(unite(K300, UndirectedGraph(1)), false);
    test(unite(K300, K300), false);

    default_random_engine engine(0);
    test(generate_connected_graph(10000, 100000, engine), true);
    test(generate_graph(100001, 99999, engine), false);

    cout << "Hello World" << endl;
}
