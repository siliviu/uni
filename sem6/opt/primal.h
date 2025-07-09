#include <bits/stdc++.h>

using namespace std;

// min <c, x>
// Ax=B
// x >= 0
// A has all canonical bases
template <typename T>
tuple<vector<T>, T, vector<int>, vector<int>> solveStandardLong(vector<T> cost, vector<vector<T>> A, vector<T> b) {
    int n = A.size(), m = A[0].size();
    assert(cost.size() <= m);
    cost.resize(m);
    assert(b.size() == n);
    println(stderr, "cost: {}", cost);
    println(stderr, "A: {}", A);
    println(stderr, "b: {}", b);

    vector<int> basis, nonbasis;

    for (int i = 0;i < n;++i) {
        vector<T> base(n);
        base[i] = 1;
        for (int j = 0;j < m;++j)
            if (isEqual(getColumn(A, j), base)) {
                basis.emplace_back(j);
                break;
            }
    }
    assert(basis.size() == n);
    println(stderr, "Basis: {}", basis);

    for (int i = 0;i < m;++i)
        if (find(basis.begin(), basis.end(), i) == basis.end())
            nonbasis.push_back(i);
    println(stderr, "Non basis: {}", nonbasis);
    assert(nonbasis.size() == m - n);

    vector<vector<T>> tableau(m - n + 1, vector<T>(n + 1, 0));

    for (int i = 1;i <= m - n;++i) {
        auto&& column = getColumn(A, nonbasis[i - 1]);
        for (int j = 1;j <= n;++j)
            tableau[i][j] = column[j - 1];
    }

    if (any_of(b.begin(), b.end(), [](T x) { return x < 0; }))
        throw runtime_error("Primal simplex method is not applicable for negative b.");

    tableau[0][0] = 1;

    for (int i = 0;i < n;++i)
        tableau[0][i + 1] = b[i];

    vector<T> basisCosts(n, 0);
    for (int i = 0;i < n;++i)
        basisCosts[i] = cost[basis[i]];


    for (int i = 1;i <= m - n;++i) {
        tableau[i][0] = inner_product(tableau[i].begin() + 1, tableau[i].end(), basisCosts.begin(), 0.0) - cost[nonbasis[i - 1]];
    }

    print(tableau);

    while (true) {
        auto dualCosts = getColumn(tableau, 0);
        if (all_of(dualCosts.begin() + 1, dualCosts.end(), [](T x) { return x <= EPSILON; }))
            break;

        int pivotLine = max_element(dualCosts.begin() + 1, dualCosts.end()) - dualCosts.begin();
        int pivotColumn = 0;

        println(stderr, "pivotLine {}", pivotLine);

        for (int i = 1;i <= m - n;++i)
            if (dualCosts[i] > 0 && *max_element(tableau[i].begin() + 1, tableau[i].end()) <= EPSILON)
                return { {}, numeric_limits<T>::min(), {}, {} };

        for (int i = 1;i <= n;++i)
            if (tableau[pivotLine][i] > 0)
                if (pivotColumn == 0 || tableau[0][i] / tableau[pivotLine][i]
                    < tableau[0][pivotColumn] / tableau[pivotLine][pivotColumn])
                    pivotColumn = i;

        println(stderr, "pivotColumn {}", pivotLine, pivotColumn);

        vector newTableau = tableau;

        for (int i = 0;i <= m - n;++i)
            newTableau[i][pivotColumn] /= tableau[pivotLine][pivotColumn];

        for (int i = 0;i <= n;++i)
            newTableau[pivotLine][i] /= -tableau[pivotLine][pivotColumn];

        newTableau[pivotLine][pivotColumn] = 1 / tableau[pivotLine][pivotColumn];

        for (int i = 0;i <= m - n;++i)
            if (i != pivotLine)
                for (int j = 0;j <= n;++j)
                    if (j != pivotColumn && (i || j))
                        newTableau[i][j] = tableau[i][j] - tableau[i][pivotColumn] * tableau[pivotLine][j] / tableau[pivotLine][pivotColumn];

        tableau = newTableau;
        swap(nonbasis[pivotLine - 1], basis[pivotColumn - 1]);
        basisCosts[pivotColumn - 1] = cost[basis[pivotColumn - 1]];

        print(tableau);
    }

    vector<T> ans(m, 0);
    for (int i = 0;i < n;++i) {
        ans[basis[i]] = tableau[0][i + 1];
    }

    vector<int> negativeObjectives;
    for (int i = 1;i <= m - n;++i)
        if (tableau[i][0] < 0)
            negativeObjectives.push_back(nonbasis[i - 1]);

    return { ans, inner_product(tableau[0].begin() + 1, tableau[0].end(), basisCosts.begin(), 0.0), basis, negativeObjectives };
}

template <typename T>
tuple<vector<T>, T> solveStandard(vector<T> cost, vector<vector<T>> A, vector<T> b) {
    auto [x, y, _, __] = solveStandardLong(cost, A, b);
    return { x,y };
}