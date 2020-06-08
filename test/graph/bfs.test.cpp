#define PROBLEM \
    "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_C"

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
            G[u].emplace_back(u, v);
        }
    }

    BFS bfs(G, 0);
    for(int i = 0; i < n; ++i) {
        cout << i + 1 << ' ' << int(bfs.path_to(i).size()) - 1 << endl;
    }
}
