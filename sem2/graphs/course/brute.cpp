// EV^2log brute
#pragma GCC optimize("unroll-loops","Ofast")
#include <bits/stdc++.h>
#define int long long

using namespace std;
using pi = pair<int, int>;

int32_t main() {
    const int INF = LLONG_MAX;
    int n, m;
    cin >> n >> m;
    vector<vector<pi>> G(n + 1);
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        G[x].emplace_back(y, z);
    }
    auto Solve = [&](const vector<vector<pi>>& G) {
        int N = G.size() - 1;
        vector dist(N + 1, vector(N + 1, INF));
        for (int i = 1; i <= N; ++i) {
            auto& dp = dist[i];
            dp[i] = 0;
            priority_queue<pi, vector<pi>, greater<pi>> PQ;
            PQ.emplace(0, i);
            while (!PQ.empty()) {
                auto [cost, node] = PQ.top();
                PQ.pop();
                if (dp[node] != cost)
                    continue;
                for (auto [x, w] : G[node])
                    if (cost + w < dp[x]) {
                        dp[x] = cost + w;
                        PQ.emplace(dp[x], x);
                    }
            }
        }
        return dist;
    };
    auto GetAnswer = [&](vector<vector<int>>&& M) {
        int n = M.size() - 1;
        vector ans(n + 1, INF);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (j != i)
                    ans[j] = min(ans[j], M[i][j]);
        return ans;
    };
    auto ans = GetAnswer(Solve(G));
    for (int i = 1;i <= n;++i)
        cout << (ans[i] == INF ? "INF" : to_string(ans[i])) << ' ';
}