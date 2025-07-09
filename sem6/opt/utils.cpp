#include <bits/stdc++.h>

using namespace std;

const long double EPSILON = 1e-9;

template <typename T>
bool isEqual(const vector<T>& a, const vector<T>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (abs(a[i] - b[i]) > EPSILON) return false;
    }
    return true;
}

template <typename T>
auto getColumn(const vector<vector<T>>& matrix, int col) {
    return matrix 
        | views::transform([col](const auto& row) { return row[col]; })
        | ranges::to<vector>();
}

template <typename T>
auto transpose(const vector<vector<T>>& matrix) {
    return views::iota(0, static_cast<int>(matrix[0].size()))
        | views::transform([&](int col) { return getColumn(matrix, col); })
        | ranges::to<vector>();
}

template<typename T>
auto multiply(const vector<vector<T>>& A, const vector<vector<T>>& B) {
    int n = A.size(), m = B[0].size(), p = B.size();
    vector<vector<T>> C(n, vector<T>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < p; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

template<typename T>
auto determinant(const vector<vector<T>>& A) {
    int n = A.size();
    assert(n == A[0].size());
    vector<vector<T>> B = A;
    T det = 1;
    for (int i = 0; i < n; ++i) {
        int pivot = -1;
        for (int j = i; j < n; ++j) {
            if (B[j][i] != 0) {
                pivot = j;
                break;
            }
        }
        if (pivot == -1) return (T)0;

        if (pivot != i) {
            swap(B[i], B[pivot]);
            det *= -1;
        }

        det *= B[i][i];
        for (int j = i + 1; j < n; ++j) {
            T factor = B[j][i] / B[i][i];
            for (int k = i; k < n; ++k) {
                B[j][k] -= factor * B[i][k];
            }
        }
    }
    return det;
}

template<typename T>
auto inverse(const vector<vector<T>>& A) {
    int n = A.size();
    assert(n == A[0].size());
    vector<vector<T>> adj(n, vector<T>(n));
    T det = determinant(A);
    if (det == 0) throw runtime_error("Matrix is singular and cannot be inverted.");

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            vector<vector<T>> submatrix(n - 1, vector<T>(n - 1));
            for (int k = 0; k < n; ++k) {
                for (int l = 0; l < n; ++l) {
                    if (k != i && l != j) {
                        submatrix[k < i ? k : k - 1][l < j ? l : l - 1] = A[k][l];
                    }
                }
            }
            adj[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * determinant(submatrix);
        }
    }

    vector<vector<T>> inv(n, vector<T>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inv[i][j] = adj[i][j] / det;
        }
    }
    return inv;
}


template<typename T>
struct std::formatter<vector<T>> : std::formatter<string> {
    auto format(const vector<T>& v, format_context& ctx) const {
        string result = "[";
        for (size_t i = 0; i < v.size(); ++i) {
            result += std::format("{}", v[i]);
            if (i < v.size() - 1) result += ", ";
        }
        result += "]";
        return formatter<string>::format(result, ctx);
    }
};

template <typename T>
void print(const vector<T>& vec) {
    for (const auto& elem : vec) {
        cerr << elem << " ";
    }
    cerr << endl;
}

template <typename T>
void print(const vector<vector<T>>& vec) {
    for (const auto& row : vec) {
        print(row);
    }
    cerr << endl;
}