#include <bits/stdc++.h>

using namespace std;

int generateRandomNumber(int upperBoundary) {
    return rand() % upperBoundary + 1;
}

int N, M, n, m, upBound = 1'000;

int main(int argc, char** argv) {
    N = stoi(argv[1]);
    M = stoi(argv[2]);
    n = stoi(argv[3]);
    m = stoi(argv[4]);
    // if (argc == 5 + 1)
        // upBound = stoi(argv[5]);
    ofstream cout("data.txt");
    cout << N << ' ' << M << ' ' << n << ' ' << m << '\n';
    for (int i = 0;i < N;++i) {
        for (int j = 0;j < M;++j) {
            cout << generateRandomNumber(upBound) << ' ';
        }
        cout << '\n';
    }
    for (int i = 0;i < n;++i) {
        for (int j = 0;j < m;++j) {
            cout << generateRandomNumber(upBound) << ' ';
        }
        cout << '\n';
    }
    cout.close();
}