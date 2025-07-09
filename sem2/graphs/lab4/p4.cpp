#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
    ifstream cin(argv[1]);
    ofstream cout(argv[2]);
    int n;
    cin >> n;
    map<char, int> mp;
    string dummy;
    getline(cin, dummy);
    while (n--) {
        char x;
        int y;
        string s;
        getline(cin, s);
        x = s[0];
        stringstream ss(s.substr(2));
        ss >> y;
        mp[x] = y;
    }
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
    string s;
    cin >> s;
    int node = PQ.top();
    for (auto x : s) {
        node = t[node].s[x - '0'];
        if (!t[node].s[0]) {
            cout << t[node].c;
            node = PQ.top();
            continue;
        }
    }
}