#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
    ifstream cin(argv[1]);
    ofstream cout(argv[2]);
    string s;
    getline(cin, s);
    map<char, int> mp;
    for (auto x : s)
        ++mp[x];
    cout << mp.size() << '\n';
    struct node {
        int f;
        char c;
        int s[2] = {};
        node() = default;
        node(char _c, int _f) : c(_c), f(_f) {};
        bool operator < (const node& b) { return make_pair(f, c) < make_pair(b.f, b.c); };
    };
    vector<node> t = { node(0,0) };
    auto comp = [&](int a, int b) {
        return t[b] < t[a];
    };
    priority_queue<int, vector<int>, decltype(comp)> PQ(comp);
    for (const auto& [x, y] : mp) {
        cout << x << ' ' << y << '\n';
        node n(x, y);
        t.emplace_back(n);
        PQ.emplace(t.size() - 1);
    }
    while (PQ.size() != 1) {
        int a = PQ.top();
        PQ.pop();
        int b = PQ.top();
        PQ.pop();
        node x;
        x.f = t[a].f + t[b].f;
        x.c = min(t[a].c, t[b].c);
        x.s[0] = a, x.s[1] = b;
        t.emplace_back(x);
        PQ.emplace(t.size() - 1);
    }
    map<char, string> encoding;
    string cur = "";
    auto dfs = [&](auto& self, int node)->void {
        if (!t[node].s[0]) {
            encoding[t[node].c] = cur;
            return;
        }
        for (int i = 0;i < 2;++i) {
            cur += '0' + i;
            self(self, t[node].s[i]);
            cur.pop_back();
        }
    };
    dfs(dfs, PQ.top());
    for (auto x : s)
        cout << encoding[x];
}