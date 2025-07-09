#include <bits/stdc++.h>
#include "primal.h"

using namespace std;

template <typename T>
void canonicalise(vector<vector<T>>& A, vector<T>& b) {
    int n = A.size(), m = A[0].size();

    vector<int> basis(n, -1), nonbasis;

    for (int i = 0;i < n;++i) {
        vector<T> base(n);
        base[i] = 1;
        for (int j = 0;j < m;++j)
            if (isEqual(getColumn(A, j), base)) {
                basis[i] = j;
                break;
            }
    }

    if (find(basis.begin(), basis.end(), -1) == basis.end()) {
        return;
    }

    for (int i = 0;i < m;++i)
        if (find(basis.begin(), basis.end(), i) == basis.end())
            nonbasis.push_back(i);

    int it = 100;

    static mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

    while (--it) {

        int needed = nonbasis.size() - n;
        auto toPickFrom = nonbasis;
        auto newBasis = basis;
        shuffle(toPickFrom.begin(), toPickFrom.end(), generator);

        for (int i = 0;i < n;++i) {
            if (newBasis[i] == -1) {
                newBasis[i] = toPickFrom.back();
                toPickFrom.pop_back();
            }
        }

        assert(find(newBasis.begin(), newBasis.end(), -1) == newBasis.end());

        println(stderr, "Basis: {}", newBasis);

        vector<vector<T>> B(n, vector<T>(n));
        for (int i = 0;i < n;++i)
            for (int j = 0;j < n;++j) {
                B[i][j] = A[i][newBasis[j]];
            }

        println(stderr, "B: {}", B);

        if (abs(determinant(B)) <= EPSILON)
            continue;

        vector<vector<T>> B_inv = inverse(B);
        println(stderr, "B_inv: {}", B_inv);

        vector<vector<T>> newA = A, newB(n, vector<T>(1));
        for (int i = 0;i < n;++i)
            newB[i][0] = b[i];

        newA = multiply(B_inv, A);
        newB = multiply(B_inv, newB);
        println(stderr, "newA: {}", newA);
        println(stderr, "newB: {}", newB);

        if (all_of(newB.begin(), newB.end(), [](const vector<T>& x) { return x[0] >= 0; })) {
            A = newA;
            b = getColumn(newB, 0);
            return;
        }
    }

    println(stderr, "Cannot transform to canonical form.");
}


template <typename T>
pair<vector<T>, T> solveAll(vector<T> cost, string type, vector<vector<T>> A, vector<string> operations, vector<T> b) {
    int n = A.size(), m = A[0].size();
    assert(cost.size() == m);
    assert(b.size() == n);

    assert(type == "max" || type == "min");

    if (type == "max") {
        for (auto& x : cost) x = -x;
    }

    for (int i = 0;i < n;++i) {
        string op = operations[i];
        assert(op == "<=" || op == ">=" || op == "=");
        if (b[i] < 0) {
            for (auto& x : A[i])
                x *= -1;
            b[i] *= -1;
            if (op == "<=")
                op = ">=";
            else if (op == ">=")
                op = "<=";
        }
        if (op != "=")
            for (int j = 0;j < n;++j)
                A[j].push_back((op == "<=" ? 1 : -1) * (i == j));
    }

    canonicalise(A, b);

    auto [ans, value] = solveStandard(cost, A, b);

    ans.resize(m);

    if (type == "max") {
        if (value == numeric_limits<T>::min())
            return { {}, numeric_limits<T>::max() };
        value *= -1;
    }

    return { ans, value };
}