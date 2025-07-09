// dijkstra

#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;

int main() {
    int s, n, m;
    cin >> n >> m >> s;
    vector<vector<pi>> G(n + 1);
    vector<int> dp(n + 1, 0x3F3F3F3F);
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        G[x].emplace_back(y, z);
    }
    priority_queue<pi, vector<pi>, greater<pi>> PQ;
    PQ.emplace(0, s);
    dp[s] = 0;
    while (!PQ.empty()) {
        auto [cost, node] = PQ.top();
        PQ.pop();
        if (dp[node] != cost)
            continue;
        for (auto x : G[node])
            if (cost + x.second < dp[x.first]) {
                dp[x.first] = cost + x.second;
                PQ.emplace(cost + x.second, x.first);
            }
    }
    for (int i = 1;i <= n;++i)
        cout << dp[i] << ' ';
}