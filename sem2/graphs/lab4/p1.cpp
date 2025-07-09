#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
    ifstream cin(argv[1]);
    ofstream cout(argv[2]);
    int n;
    cin >> n;
    vector<vector<int>> G(n + 1);
    vector<int> p(n + 1), s(n + 1);
    int root = -1;
    for (int i = 0;i < n;++i) {
        int x;
        cin >> x;
        p[i] = x;
        if (x == -1) {
            root = i;
            continue;
        }
        ++s[i], ++s[x];
        G[i].emplace_back(x);
        G[x].emplace_back(i);
    }
    priority_queue<int, vector<int>, greater<int>> Q;
    for (int i = 0;i < n;++i)
        if (s[i] == 1 && i != root)
            Q.emplace(i);
    cout << n - 1 << '\n';
    while (!Q.empty()) {
        int node = Q.top();
        Q.pop();
        // cerr << "NODE: " << node << '\n';
        cout << p[node] << ' ';
        for (auto x : G[node])
            if (--s[x] == 1 && x != root)
                Q.emplace(x);
    }
    cout.close();
}
