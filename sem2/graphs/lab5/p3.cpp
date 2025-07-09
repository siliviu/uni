#include <bits/stdc++.h>

using namespace std;

// log

// int main(int argc, char** argv) {
//     // ifstream cin(argv[1]);
//     // ofstream cout(argv[2]);
//     int n, m;
//     cin >> n >> m;
//     vector<set<int>> G(n);
//     while (m--) {
//         int x, y;
//         cin >> x >> y;
//         G[x].emplace(y);
//         G[y].emplace(x);
//     }
//     stack<int> st;
//     vector<int> ans;
//     st.emplace(0);
//     while (!st.empty()) {
//         int node = st.top();
//         if (G[node].empty()) {
//             ans.emplace_back(node);
//             st.pop();
//         }
//         else {
//             int x = *G[node].begin();
//             G[node].erase(x);
//             G[x].erase(node);
//             st.emplace(x);
//         }
//     }
//     reverse(ans.begin(), ans.end());
//     ans.pop_back();
//     for (auto x : ans)
//         cout << x << ' ';
//     cout << '\n';
// }

// linear

int main(int argc, char** argv) {
    ifstream cin(argv[1]);
    ofstream cout(argv[2]);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> G(n);
    vector<int> seen(m);
    for (int i = 0;i < m;++i) {
        int x, y;
        cin >> x >> y;
        G[x].emplace_back(y, i);
        G[y].emplace_back(x, i);
    }
    stack<int> st;
    vector<int> ans;
    st.emplace(0);
    while (!st.empty()) {
        int node = st.top();
        if (G[node].empty()) {
            ans.emplace_back(node);
            st.pop();
        }
        else {
            auto [x, nr] = G[node].back();
            G[node].pop_back();
            if (seen[nr])
                continue;
            seen[nr] = 1;
            st.emplace(x);
        }
    }
    reverse(ans.begin(), ans.end());
    ans.pop_back();
    for (auto x : ans)
        cout << x << ' ';
    cout << '\n';
}

