#include <bits/stdc++.h>

using namespace std;

int N, M, n, m, P = 1;


int getElement(int in[10'000][10'000], int i, int j) {
    i = max(i, 0);
    j = max(j, 0);
    i = min(i, N - 1);
    j = min(j, M - 1);
    return in[i][j];
}

void task(int in[10'000][10'000], int conv[10'000][10'000], int startY, int endY, int startX, int endX, int ans[10'000][10'000]) {
    for (int i = startY;i < endY;++i)
        for (int j = startX;j < endX;++j)
            for (int di = -n / 2;di <= n / 2;++di)
                for (int dj = -m / 2;dj <= m / 2;++dj)
                    ans[i][j] += getElement(in, i + di, j + dj) * conv[n / 2 + di][m / 2 + dj];
}

void taskDistribution(int in[10'000][10'000], int conv[10'000][10'000], vector<pair<int, int>> indexes, int ans[10'000][10'000]) {
    for (auto [i, j] : indexes)
        for (int di = -n / 2;di <= n / 2;++di)
            for (int dj = -m / 2;dj <= m / 2;++dj)
                ans[i][j] += getElement(in, i + di, j + dj) * conv[n / 2 + di][m / 2 + dj];
}

void test(auto&& function) {
    auto t_start = std::chrono::high_resolution_clock::now();
    function();
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
    std::cout << setprecision(10) << elapsed_time_ms << "\n";
}

int in[10'000][10'000], conv[10'000][10'000], ansDo[10'000][10'000];

int main(int argc, char** argv) {
    // N = stoi(argv[1]);
    // M = stoi(argv[2]);
    // n = stoi(argv[3]);
    // m = stoi(argv[4]);
    P = stoi(argv[1]);
    string type = string(argv[2]);
    string out = string(argv[3]);
    srand(time(0));

    ifstream cin("data.txt");
    cin >> N >> M >> n >> m;

    for (int i = 0;i < N;++i)
        for (int j = 0;j < M;++j)
            cin >> in[i][j];

    for (int i = 0;i < n;++i)
        for (int j = 0;j < m;++j)
            cin >> conv[i][j];

    // vector<vector<int>> ansCheck(N, vector<int>(M));
    // task(in, conv, 0, N, 0, M, ansCheck);

    test([&]() {
        if (P == 1) {
            task(in, conv, 0, N, 0, M, ansDo);
            return;
        }
        vector<thread> threads(P);
        if (type == "LINE") {
            int block = N / P, remainder = N % P;
            int start = 0, end = block;
            for (int i = 0;i < P;++i) {
                if (remainder) {
                    ++end;
                    --remainder;
                }
                threads[i] = thread(task, ref(in), ref(conv), start, end, 0, M, ref(ansDo));
                start = end;
                end = start + block;
            }
        }
        else if (type == "COLUMN") {
            int block = M / P, remainder = M % P;
            int start = 0, end = block;
            for (int i = 0;i < P;++i) {
                if (remainder) {
                    ++end;
                    --remainder;
                }
                threads[i] = thread(task, ref(in), ref(conv), 0, N, start, end, ref(ansDo));
                start = end;
                end = start + block;
            }
        }
        else if (type == "BLOCK") {
            int blocky = N / sqrt(P), blockx = M / sqrt(P), cur = 0;
            for (int i = 0;i < N;i += blocky)
                for (int j = 0;j < M;j += blockx) {
                    threads[cur++] = thread(task, ref(in), ref(conv), i, i + blocky, j, j + blockx, ref(ansDo));
                }
        }
        else if (type == "DISTRIBUTION") {
            auto linear_distribution = [&](int thread) {
                vector<pair<int, int>> indexes;
                int block = N * M / P;
                auto numberToPair = [&](int nr) {
                    return make_pair(nr / M, nr % M);
                    };
                for (int i = thread * block;i < (thread + 1) * block; ++i)
                    indexes.push_back(numberToPair(i));
                return indexes;
                };
            for (int i = 0;i < P;++i)
                threads[i] = thread(taskDistribution, ref(in), ref(conv), linear_distribution(i), ref(ansDo));
        }
        for (auto& x : threads)
            x.join();
        }
    );

    ofstream cout(out);
    for (int i = 0;i < N;++i) {
        for (int j = 0;j < M;++j)
            cout << ansDo[i][j] << ' ';
        cout << '\n';

    }

    // assert(ansCheck == ansDo);
}