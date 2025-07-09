#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
    ifstream cin(argv[1]);
    ofstream cout(argv[2]);
    int n, c = 0, l;
    cin >> n;
    ++n;
    vector<int> d(n, 1), a(n - 2), p(n, -1);
    int root;
    for (auto& x : a) {
        cin >> x;
        ++d[x];
    }
    cin >> root;
    for (; d[c] != 1 || c == root; ++c);
    l = c;
    for (auto x : a) {
        p[l] = x;
        // cout << l << ' ' << x << '\n';
        if (x != root && --d[x] == 1 && x < c) {
            l = x;
            continue;
        }
        for (++c; d[c] != 1 || c == root; ++c);
        l = c;
    }
    p[l] = root;
    // cout << l << ' ' << root << '\n';
    cout << n << '\n';
    for (auto x : p)
        cout << x << ' ';
}