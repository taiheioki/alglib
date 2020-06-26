#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0086"

#include <iostream>
#include <string>

#include "alglib/graph/eulerian_trail.hpp"

using namespace std;
using namespace alg;

int main()
{
    DirectedGraph G(26);

    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        string word;
        cin >> word;
        G.add_edge(word[0] - 'a', word.back() - 'a');
    }

    EulerianTrailHierholzer euler(G);
    cout << (euler.result == EulerianTrailHierholzer::Result::Eulerian ? "OK" : "NG") << endl;
}
