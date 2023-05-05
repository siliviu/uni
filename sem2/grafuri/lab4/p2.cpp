// #include <bits/stdc++.h>

// using namespace std;

// int main(int argc, char** argv) {
//     // ifstream cin(argv[1]);
//     // ofstream cout(argv[2]);
//     int n, c = 0, l;
//     cin >> n;
//     cout << n + 1 << '\n';
//     vector<int> d(n + 1, 1), a(n), p(n + 1, -1);
//     for (auto& x : a) {
//         cin >> x;
//         ++d[x];
//     }
//     --d[a.back()];
//     a.pop_back();
//     for (;d[c] != 1;++c);
//     l = c;
//     for (auto x : a) {
//         p[l] = x;
//         cout << l << ' ' << x << '\n';
//         if (--d[x] == 1 && x < c) {
//             l = x;
//             continue;
//         }
//         for (++c;d[c] != 1;++c)
//             l = c;
//     }
//     for (int i = 0;i <= n;++i)
//         cout << p[i] << ' ';
// }
// #include <bits/stdc++.h>

// using namespace std;

// int main() {
//     ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//     int n, c = 1, l;
//     cin >> n;
//     ++n;
//     vector<int> d(n + 1, 1), a(n - 2), p(n + 1, 1);
//     for (auto& x : a) {
//         cin >> x;
//         ++x;
//         ++d[x];
//     }
//     int root;
//     cin >> root;
//     p[++root] = -1;
//     for (; d[c] != 1; ++c);
//     l = c;
//     for (auto x : a) {
//         p[l] = x;
//         cout << l << ' ' << x << '\n';
//         if (--d[x] == 1 && x < c) {
//             l = x;
//             continue;
//         }
//         for (++c; d[c] != 1; ++c);
//         l = c;
//     }
//     cout << n << '\n';
//     for (int i = 1;i <= n;++i)
//         cout << p[i] - 1 << ' ';
//     // cout << l << ' ' << n;
// }
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, c = 1, l;
    cin >> n;
    ++n;
    vector<int> d(n + 1, 1), a(n - 2), p(n + 1);
    for (auto& x : a) {
        cin >> x;
        ++x;
        ++d[x];
    }
    for (; d[c] != 1; ++c);
    l = c;
    for (auto x : a) {
        p[l] = x;
        cout << l << ' ' << x << '\n';
        if (--d[x] == 1 && x < c) {
            l = x;
            continue;
        }
        for (++c; d[c] != 1; ++c);
        l = c;
    }
    p[l] = n;
    cout << l << ' ' << n;
    for (int i = 1;i <= n;++i)
        cout << p[i] - 1 << ' ';
}