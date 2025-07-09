#include <bits/stdc++.h>

using namespace std;

int generateRandomNumber() {
    return rand() % 10;
}

int T;

int main(int argc, char** argv) {
    T = stoi(argv[1]);
    assert(T >= 1 && T <= 5);
    int N1, N2;
    vector<int> a1, a2;
    if (T == 1) {
        N1 = N2 = 18;
        a1 = a2 = { 1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9 };
    }
    else if (T == 4) {
        N1 = N2 = 16;
        a1 = { 9,9,9,9,4,4,4,4,9,9,9,9,9,9,9,9 };
        a2 = { 9,9,9,9,5,5,5,5,9,9,9,9,9,9,9,9 };
    }
    else if (T == 2 || T == 3 || T == 5) {
        if (T == 2)
            N1 = N2 = 1000;
        else if (T == 3)
            N1 = 100, N2 = 100'000;
        else if (T == 5)
            N1 = N2 = 100'000'000;
        for (int i = 0;i < N1;++i)
            a1.emplace_back(generateRandomNumber());
        for (int i = 0;i < N2;++i)
            a2.emplace_back(generateRandomNumber());
    }
    ofstream cout1("Numar1.txt");
    cout1 << N1 << '\n';
    for (auto x : a1)
        cout1 << x;
    cout1.close();
    ofstream cout2("Numar2.txt");
    cout2 << N2 << '\n';
    for (auto x : a2)
        cout2 << x;
    cout2.close();
}