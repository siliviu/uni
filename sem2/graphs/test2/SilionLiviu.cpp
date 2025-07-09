// pb de 10
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
    // ifstream cin("test.in");
    // ofstream cout(argv[2]);
    int n, m;
    cin >> n >> m;
    int s = 0, t = n - 1;
    vector<vector<int>> G(n), c(n, vector<int>(n));
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        G[x].emplace_back(y);
        G[y].emplace_back(x);
        c[x][y] += z;
    }
    int flow = 0;
    while (1) {
        vector<int> p(n, -1);
        queue<int> Q;
        Q.emplace(s);
        p[s] = 0;
        while (!Q.empty()) {
            int node = Q.front();
            Q.pop();
            for (auto x : G[node])
                if (p[x] == -1 && c[node][x]) {
                    Q.emplace(x);
                    p[x] = node;
                }
        }
        if (p[t] == -1)
            break;
        int curflow = INT_MAX;
        for (int i = t;i != s;i = p[i])
            curflow = min(curflow, c[p[i]][i]);
        for (int i = t;i != s;i = p[i]) {
            c[p[i]][i] -= curflow;
            c[i][p[i]] += curflow;
        }
        flow += curflow;
    }
    cout << flow;
}