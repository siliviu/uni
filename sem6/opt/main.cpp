#include <bits/stdc++.h>
#include "utils.cpp"

#ifdef CHEAT
#include "cheat.h"
#endif
#ifdef TWOPHASE
#include "twophase.h"
#endif

template <typename T>
pair<vector<T>, T> solveAll(vector<T> cost, string type, vector<vector<T>> A, vector<string> operations, vector<T> b);

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 2) {
        string path = "tests/" + string(argv[1]);
        freopen(path.c_str(), "r", stdin);
    }

    string type;
    cin >> type;
    vector<double> cost;
    string line;
    cin.get();
    getline(cin, line), getline(cin, line);
    stringstream ss(line);
    double x;
    while (ss >> x)
        cost.push_back(x);
    int n, m;
    cin >> n >> m;
    vector<vector<double>> A(n, vector<double>(m));
    vector<string> operations(n);
    vector<double> b(n);
    for (int i = 0;i < n;++i) {
        for (int j = 0;j < m;++j)
            cin >> A[i][j];
        cin >> operations[i];
        cin >> b[i];
    }

    auto [ans, value] = solveAll(cost, type, A, operations, b);

    if (value == numeric_limits<double>::min()) {
        println("Unbounded, answer is -inf");
        return 0;
    }
    else if (value == numeric_limits<double>::max()) {
        println("Unbounded, answer is +inf");
        return 0;
    }
    println("Solution: {}", ans);
    println("Value: {}", value);
}