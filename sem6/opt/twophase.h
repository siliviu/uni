#include <bits/stdc++.h>
#include "primal.h"

using namespace std;

template <typename T>
void twoStep(vector<T>& cost, vector<vector<T>>& A, vector<T>& b) {
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

    int artificialVaribles = 0;

    for (int i = 0;i < n;++i) {
        if (basis[i] == -1) {
            basis[i] = m + artificialVaribles;
            ++artificialVaribles;
            for (auto& y : A)
                y.push_back(0);
            A[i][basis[i]] = 1;
        }
    }

    vector<T> artificialCosts(m + artificialVaribles, 0);
    for (int i = 0;i < artificialVaribles;++i)
        artificialCosts[m + i] = 1;
    auto [ans, value, phase1Basis, negativeObjectives] = solveStandardLong(artificialCosts, A, b);

    println("Phase1 basis {}", phase1Basis);
    println("Phase1 value {}", value);

    if (abs(value) > EPSILON) {
        println("Unfeasible");
        throw runtime_error("Unfeasible");
    }

    for (int i = 0;i < artificialVaribles;++i)
        for (auto& y : A)
            y.pop_back();

    auto newBasis = phase1Basis;
    int newArtificialVaribles = 0;

    for (int i = 0;i < n;++i)
        if (phase1Basis[i] >= m) {
            newBasis[i] = m + newArtificialVaribles;
            ++newArtificialVaribles;
            for (auto& y : A)
                y.push_back(0);
            A[i][newBasis[i]] = 1;
        }

    for (auto& x : negativeObjectives)
        if (x < m) {
            cost[x] = 0;
            for (auto& y : A)
                y[x] = 0;
        }

    println(stderr, "Basis: {}", newBasis);

    vector<vector<T>> B(n, vector<T>(n));
    for (int i = 0;i < n;++i)
        for (int j = 0;j < n;++j) {
            B[i][j] = A[i][newBasis[j]];
        }

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

    twoStep(cost, A, b);

    auto [ans, value] = solveStandard(cost, A, b);

    ans.resize(m);

    if (type == "max") {
        if (value == numeric_limits<T>::min())
            return { {}, numeric_limits<T>::max() };
        value *= -1;
    }

    return { ans, value };
}