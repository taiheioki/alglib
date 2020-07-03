#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=10000"

#include <iostream>
#include <random>
#include <vector>

#include "alglib/graph/eulerian_trail.hpp"
#include "generate.hpp"
#include "verify.hpp"

using namespace std;
using namespace alg;

void solve(const DirectedGraph& G)
{
    verify(G, EulerianTrailHierholzer(G));
}

int main()
{
    const vector<Data> data = {
        {0, 0, true},
        {1, 1, true},
        {10, 20, true},
        {10, 20, false},
        {100, 300, true},
        {100, 300, false},
        {100, 5000, true},
        {100, 5000, false},
        {10000, 10000, true},
        {10000, 10000, false},
        {10000, 200000, true},
        {10000, 200000, false},
        {100000, 300000, true},
        {100000, 300000, false},
        {500000, 500000, true},
        {500000, 500000, false},
    };
    default_random_engine engine(0);

    for(int i = 0; i < int(data.size()); ++i) {
        cerr << "Case #" << i << endl;
        solve(generate_directed(data[i], engine));
    }

    cout << "Hello World" << endl;
}
