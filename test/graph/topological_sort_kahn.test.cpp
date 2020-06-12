#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B"

#include <iostream>
#include "alglib/graph/topological_sort.hpp"

using namespace std;
using namespace alg;

int main()
{
    int n, m;
    cin >> n >> m;
    Graph G(n);

    for(int j = 0; j < m; ++j) {
        int s, t;
        cin >> s >> t;
        G[s].push_back({s, t});
    }

    const TopologicalSortKahn top(G);
    for(const int v : top.order) {
        cout << v << endl;
    }
}
