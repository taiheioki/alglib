#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_A"

#include <iostream>

#include "alglib/graph/topological_sort.hpp"
#include "verify.hpp"

using namespace std;
using namespace alg;

int main()
{
    int n, m;
    cin >> n >> m;
    DirectedGraph G(n);

    for(int j = 0; j < m; ++j) {
        int s, t;
        cin >> s >> t;
        G.add_edge(s, t);
    }

    const TopologicalSortTarjan top(G);
    verify(G, top);

    cout << !top.is_dag << endl;
}
