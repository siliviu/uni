#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
    ifstream cin(argv[1]);
    ofstream cout(argv[2]);
    int n, m;
    cin >> n >> m;
    int s = 0, t = n - 1;
    vector<vector<int>> G(n);
    vector<vector<int>> c(n, vector<int>(n));
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        G[x].emplace_back(y);
        G[y].emplace_back(x);
        c[x][y] += z;
    }
    int flow = 0;
    while (1) {
        queue<int> Q;
        vector<int> p(n, -1);
        Q.emplace(s);
        p[s] = 0;
        while (!Q.empty()) {
            int node = Q.front();
            Q.pop();
            // cerr << node << '\n';
            for (auto x : G[node])
                if (p[x] == -1 && c[node][x]) {
                    p[x] = node;
                    Q.emplace(x);
                }
        }
        int cur_flow = INT_MAX;
        if (p[t] == -1)
            break;
        for (int cur = t; cur != s; cur = p[cur])
            cur_flow = min(cur_flow, c[p[cur]][cur]);
        for (int cur = t; cur != s; cur = p[cur]) {
            c[p[cur]][cur] -= cur_flow;
            c[cur][p[cur]] += cur_flow;
        }
        flow += cur_flow;
    }
    cout << flow;
}
