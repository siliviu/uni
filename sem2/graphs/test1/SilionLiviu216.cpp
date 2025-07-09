#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m, cx, cy;
    cin >> n >> m >> cx >> cy;
    vector<vector<int>> G(n + 1);
    while (m--) {
        int x, y;
        cin >> x >> y;
        G[x].emplace_back(y);
        G[y].emplace_back(x);
    }
    queue<int> Q;
    vector<int> d(n + 1), p(n + 1, -1);
    d[cx] = 1;
    Q.emplace(cx);
    while (!Q.empty()) {
        int node = Q.front();
        Q.pop();
        for (auto x : G[node])
            if (!d[x]) {
                d[x] = d[node] + 1;
                p[x] = node;
                Q.emplace(x);
            }
    }
    cout << "Lungime drumului este: " << d[cy] - 1 << '\n';
    vector<int> sol;
    for (int i = cy;i != -1;i = p[i])
        sol.emplace_back(i);
    reverse(sol.begin(), sol.end());
    cout << "Drumul este: ";
    for (auto x : sol)
        cout << x << ' ';
}