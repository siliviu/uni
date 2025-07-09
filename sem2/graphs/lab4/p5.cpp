#include <bits/stdc++.h>

using namespace std;
using ti = tuple<int, int, int>;

int main(int argc, char** argv) {
    ifstream cin(argv[1]);
    ofstream cout(argv[2]);
    int n, m;
    cin >> n >> m;
    vector<ti> E(m);
    for (auto& [x, y, z] : E)
        cin >> x >> y >> z;
    sort(E.begin(), E.end(), [&](const ti& a, const ti& b) {return get<2>(a) < get<2>(b);});
    vector<int> p(n), s(n, 1);
    iota(p.begin(), p.end(), 0);
    auto get = [&](auto& self, int x)->int {
        if (p[x] == x)
            return x;
        return p[x] = self(self, p[x]);
    };
    auto unite = [&](int x, int y) {
        x = get(get, x), y = get(get, y);
        if (x == y)
            return;
        if (s[x] > s[y])
            swap(x, y);
        s[x] += s[y];
        p[y] = x;
    };
    int cost = 0;
    vector<pair<int, int>> mst;
    for (auto& [x, y, z] : E)
        if (get(get, x) != get(get, y)) {
            cost += z;
            mst.emplace_back(x, y);
            unite(x, y);
        }
    sort(mst.begin(), mst.end());
    cout << cost << '\n' << n - 1 << '\n';
    for (auto& [x, y] : mst)
        cout << x << ' ' << y << '\n';
    cout.close();
}
