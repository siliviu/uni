#include <bits/stdc++.h>

using namespace std;

int main() {
    // read edges
    int n, m;
    cin >> n >> m;
    // common for task 1 and tasks 2(a, b)
        // vector<pair<int, int>> edges(m);
        // for (auto& [x, y] : edges)
            // cin >> x >> y;
    // task 1
        // // convert to adjacency matrix
        // vector<vector<int>> adj(n + 1, vector<int>(n + 1));
        // for (auto [x, y] : edges)
        //     adj[x][y] = adj[y][x] = 1;
        // for (int i = 1;i <= n;++i)
        //     for (int j = 1;j <= n;++j)
        //         cout << adj[i][j] << " \n"[j == n];

    // task 2 (a, b)
        // // convert to adjacency list
        // vector<vector<int>> G(n + 1);
        // // for (auto [x, y] : edges)
        // while (m--) {
        //     int x, y;
        //     cin >> x >> y;
        //     G[x].emplace_back(y), G[y].emplace_back(x);
        // }
        // vector<int> isolated;
        // for (int i = 1;i <= n;++i)
        //     if (G[i].empty())
        //         isolated.emplace_back(i);
        // cout << "Isolated nodes are: ";
        // for (auto x : isolated)
        //     cout << x << ' ';
        // cout << '\n';
        // int deg = G[1].size(), reg = 1;
        // for (int i = 2;i <= n;++i)
        //     if (G[i].size() != deg) {
        //         reg = 0;
        //         break;
        //     }
        // cout << "The graph " << (reg ? "IS" : "IS NOT") << " regular\n";

    // task 2 (c, d)
    // const int inf = 0x3F3F3F3F;
    // vector<vector<int>> dp(n + 1, vector<int>(n + 1, inf));
    // while (m--) {
    //     int x, y;
    //     cin >> x >> y;
    //     dp[x][y] = dp[y][x] = 1;
    // }
    // for (int i = 1;i <= n;++i)
    //     dp[i][i] = 0;
    // for (int k = 1;k <= n;++k)
    //     for (int i = 1;i <= n;++i)
    //         for (int j = 1;j <= n;++j)
    //             dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
    // int connected = 1;
    // for (int i = 1;i <= n;++i) {
    //     for (int j = 1;j <= n;++j) {
    //         if (dp[i][j] == inf)
    //             cout << "INF ", connected = 0;
    //         else
    //             cout << dp[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
    // cout << "The graph " << (connected ? "is" : "is not") << " connected";
}