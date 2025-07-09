#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main(int argc, char** argv) {
    ifstream cin(argv[1]);
    ofstream cout(argv[2]);
    int n, m, s, t;
    cin >> n >> m;/* >> s >> t;*/
    // --s, --t;
    s = 0, t = n - 1;
    vector<vector<pair<int, int>>> G(n);
    vector<vector<int>> hlist(2 * n);
    vector<ll> c(2 * m + 2), e(n);
    vector<int> h(n), pos(n);
    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        // --x, --y;
        G[x].emplace_back(y, 2 * i);
        G[y].emplace_back(x, 2 * i + 1);
        c[2 * i] = z;
    }
    int curh = 0;
    h[s] = n;
    auto Push = [&](int node, int x, int edge, ll flow) {
        if (!e[x] && x != t)
            hlist[h[x]].emplace_back(x);
        e[x] += flow, e[node] -= flow;
        c[edge] -= flow, c[edge ^ 1] += flow;
    };
    auto Relabel = [&](int node) {
        int minh = INT_MAX, cur = 0, z = 0;
        for (const auto [x, edge] : G[node]) {
            if (c[edge] && minh > h[x] + 1)
                minh = h[x] + 1, z = cur;
            ++cur;
        }
        pos[node] = z;
        h[node] = curh = minh;
    };
    for (const auto [x, edge] : G[s])
        Push(s, x, edge, c[edge]);
    while (1) {
        for (;hlist[curh].empty();--curh)
            if (!curh) {
                cout << e[t];
                return 0;
            }
        int node = hlist[curh].back();
        hlist[curh].pop_back();
        while (e[node]) {
            if (pos[node] == G[node].size()) {
                Relabel(node);
                continue;
            }
            const auto [x, edge] = G[node][pos[node]];
            if (c[edge] && h[node] == h[x] + 1)
                Push(node, x, edge, min(c[edge], e[node]));
            ++pos[node];
        }
    }
}