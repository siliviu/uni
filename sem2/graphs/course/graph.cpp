// Liviu Silion
// O(VE), no negative cycles
#pragma GCC optimize("unroll-loops","Ofast")
#include <bits/stdc++.h>
#define int long long

using namespace std;
using pi = pair<int, int>;

int32_t main() {
    const int INF = LLONG_MAX;
    int n, m;
    cin >> n >> m;
    vector<vector<pi>> G(n + 1), GT(n + 1);
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        G[x].emplace_back(y, z);
        GT[y].emplace_back(x, z);
    }
    vector ans(n + 1, INF), dp(n + 1, INF);
    for (int i = 1; i <= n; ++i)
        G[0].emplace_back(i, 0);
    queue<int> Q;
    vector<int> inq(n + 1), buf(n + 1), subtree(n + 1), p(n + 1);
    Q.emplace(0);
    dp[0] = 0;
    inq[0] = 1;
    while (!Q.empty()) {
        int node = Q.front();
        Q.pop(), inq[node] = 0;
        for (auto [x, cost] : G[node])
            if (dp[node] + cost < dp[x]) {
                dp[x] = dp[node] + cost;
                p[x] = node;
                if (!inq[x])
                    Q.emplace(x), inq[x] = 1;
            }
    }
    vector<vector<int>> T(n + 1);
    for (int i = 1; i <= n; ++i)
        T[p[i]].emplace_back(i);
    auto dfs = [&](auto& self, int node, int col) -> void {
        subtree[node] = col;
        for (auto x : T[node])
            self(self, x, col);
    };
    for (auto x : T[0])
        dfs(dfs, x, x);
    for (int i = 1; i <= n; ++i) {
        auto dfs = [&](auto& self, int node, int mode) -> void {
            if (node != i) {
                swap(buf[node], dp[node]);
                if (mode) {
                    Q.emplace(node);
                    inq[node] = 1;
                    for (auto [x, w] : GT[node])
                        if (subtree[x] != subtree[node])
                            dp[node] = min(dp[node], dp[x] + w);
                }
            }
            for (auto x : T[node])
                self(self, x, mode);
        };
        if (!p[i]) {
            dfs(dfs, i, 1);
            while (!Q.empty()) {
                int node = Q.front();
                Q.pop(), inq[node] = 0;
                for (auto [x, cost] : G[node])
                    if (subtree[x] == subtree[node] && dp[node] + cost < dp[x]) {
                        dp[x] = dp[node] + cost;
                        if (!inq[x])
                            Q.emplace(x), inq[x] = 1;
                    }
            }
        }
        for (auto [x, w] : GT[i])
            ans[i] = min(ans[i], dp[x] + w);
        if (!p[i])
            dfs(dfs, i, 0);
    }
    for (int i = 1;i <= n;++i)
        cout << (ans[i] == INF ? "INF" : to_string(ans[i])) << ' ';
}