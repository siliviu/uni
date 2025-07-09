#include <bits/stdc++.h>

using namespace std;

int N, M, n, m, P = 1;
pthread_barrier_t mybarrier;

int getElement(vector<vector<int>>& mat, int i, int j) {
    i = max(i, 0);
    j = max(j, 0);
    i = min(i, N - 1);
    j = min(j, M - 1);
    return mat[i][j];
}

void task(vector<vector<int>>& mat, vector<vector<int>>& conv, int startY, int endY) {
    assert(n == 3 && m == 3);
    vector<int> up, down;
    int upIndex = max(startY - 1, 0), downIndex = min(endY, M - 1);
    up = mat[upIndex];
    down = mat[downIndex];
    for (int i = startY;i < endY;++i) {
        vector<int> newUp = mat[i];
        for (int j = 0;j < M;++j) {
            mat[i][j] = 0;
            for (int di = -n / 2;di <= n / 2;++di)
                for (int dj = -m / 2;dj <= m / 2;++dj) {
                    int val;
                    if (di == -1)
                        val = up[min(max(0, j + dj), M - 1)];
                    else if (di == 0)
                        val = newUp[min(max(0, j + dj), M - 1)];
                    else if (i == endY - 1 && di == 1)
                        val = down[min(max(0, j + dj), M - 1)];
                    else
                        val = getElement(mat, i + di, j + dj);
                    mat[i][j] += val * conv[n / 2 + di][m / 2 + dj];
                }
        }
        up = newUp;
    }
}

void taskParallel(vector<vector<int>>& mat, vector<vector<int>>& conv, int startY, int endY) {
    assert(n == 3 && m == 3);
    vector<int> up, down;
    int upIndex = max(startY - 1, 0), downIndex = min(endY, M - 1);
    up = mat[upIndex];
    down = mat[downIndex];
    pthread_barrier_wait(&mybarrier);
    for (int i = startY;i < endY;++i) {
        vector<int> newUp = mat[i];
        for (int j = 0;j < M;++j) {
            mat[i][j] = 0;
            for (int di = -n / 2;di <= n / 2;++di)
                for (int dj = -m / 2;dj <= m / 2;++dj) {
                    int val;
                    if (di == -1)
                        val = up[min(max(0, j + dj), M - 1)];
                    else if (di == 0)
                        val = newUp[min(max(0, j + dj), M - 1)];
                    else if (i == endY - 1 && di == 1)
                        val = down[min(max(0, j + dj), M - 1)];
                    else
                        val = getElement(mat, i + di, j + dj);
                    mat[i][j] += val * conv[n / 2 + di][m / 2 + dj];
                }
        }
        up = newUp;
    }
}


void test(auto&& function) {
    auto t_start = std::chrono::high_resolution_clock::now();
    function();
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
    std::cout << setprecision(10) << elapsed_time_ms << "\n";
}

int main(int argc, char** argv) {
    P = stoi(argv[1]);
    string out = string(argv[2]);

    ifstream cin("data.txt");
    cin >> N >> M >> n >> m;

    assert(n == 3 && m == 3);

    vector<vector<int>> mat(N, vector<int>(M));
    vector<vector<int>> conv(n, vector<int>(m));
    for (auto& y : mat)
        for (auto& x : y)
            cin >> x;
    for (auto& y : conv)
        for (auto& x : y)
            cin >> x;

    vector<vector<int>> ansDo(N, vector<int>(M));
    test([&]() {
        if (P == 1) {
            task(mat, conv, 0, N);
            return;
        }
        vector<thread> threads(P);
        pthread_barrier_init(&mybarrier, NULL, P);
        int block = N / P, remainder = N % P;
        int start = 0, end = block;
        for (int i = 0;i < P;++i) {
            if (remainder) {
                ++end;
                --remainder;
            }
            threads[i] = thread(taskParallel, ref(mat), ref(conv), start, end);
            start = end;
            end = start + block;
        }
        for (auto& x : threads)
            x.join();
        pthread_barrier_destroy(&mybarrier);
        }
    );

    ofstream cout(out);
    for (auto& y : mat) {
        for (auto& x : y)
            cout << x << ' ';
        cout << '\n';
    }
}