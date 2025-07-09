// johnson

#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pi>> G(n + 1);
    vector<tuple<int, int, int>> E(m);
    for (auto& [x, y, z] : E) {
        cin >> x >> y >> z;
        G[x].emplace_back(y, z);
    }
    for (int i = 1;i <= n;++i)
        G[0].emplace_back(i,0);
    vector<int> w(n + 1, 0x3F3F3F3F);
    w[0] = 0;
    for (int i = 0;i < n;++i)
        for (auto [x, y, z] : E)
            w[y] = min(w[y], w[x] + z);
    for (int s = 1;s <= n;++s) {
        vector<int> dp(n + 1, 0x3F3F3F3F);
        priority_queue<pi, vector<pi>, greater<pi>> PQ;
        PQ.emplace(0, s);
        dp[s] = 0;
        while (!PQ.empty()) {
            auto [cost, node] = PQ.top();
            PQ.pop();
            if (dp[node] != cost)
                continue;
            for (auto x : G[node])
                if (cost + w[node] - w[x.first] + x.second < dp[x.first]) {
                    dp[x.first] = cost + w[node] - w[x.first] + x.second;
                    PQ.emplace(cost + w[node] - w[x.first] + x.second, x.first);
                }
        }
        for (int i = 1;i <= n;++i)
            cout << dp[i] + w[i] - w[s] << ' ';
        cout << '\n';
    }
}