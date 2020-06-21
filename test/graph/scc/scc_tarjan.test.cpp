#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include <iostream>
#include "alglib/graph/scc.hpp"

using namespace std;
using namespace alg;

int main()
{
    int n, m;
    cin >> n >> m;
    DirectedGraph G(n);

    for(int j = 0; j < m; ++j) {
        int a, b;
        cin >> a >> b;
        G.add_edge(a, b);
    }

    const auto sccs = SccTarjan(G).components;
    cout << sccs.size() << endl;

    for(const auto& scc : sccs) {
        cout << scc.size();
        for(const int v : scc) {
            cout << ' ' << v;
        }
        cout << endl;
    }
}
