#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C"

#include <iostream>
#include "alglib/graph/bfs.hpp"

using namespace std;
using namespace alg;

int main()
{
    int n;
    cin >> n;
    Graph G(n);

    for(int i = 0; i < n; ++i) {
        int u, k;
        cin >> u >> k;
        --u;
        for(int j = 0; j < k; ++j) {
            int v;
            cin >> v;
            --v;
            G.add_edge(u, v);
        }
    }

    const BFS bfs(G, 0);
    const auto d = bfs.distance_list();
    for(int i = 0; i < n; ++i) {
        cout << i + 1 << ' ' << (d[i] != BFS::Unreachable ? d[i] : -1) << endl;
    }
}
