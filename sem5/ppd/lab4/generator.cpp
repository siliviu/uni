#include <bits/stdc++.h>

using namespace std;

int generateRandomNumber(int lowerBound, int upperBound) {
    return rand() % (upperBound - lowerBound) + lowerBound;
}

int generateRandomNumber(int upperBound) {
    return rand() % upperBound + 1;
}

int N, M, n, m, upBound = 1'000;

int main() {
    int countries = 5, rounds = 10;
    int lowerBoundContestants = 80, upperBoundContestants = 100;
    int chanceDisqualified = 2, chanceNull = 10, maxScore = 100;
    int lastId = 1;
    for (int i = 0;i < countries;++i) {
        int contestants = generateRandomNumber(lowerBoundContestants, upperBoundContestants);
        for (int j = 0;j < rounds;++j) {
            ofstream cout(format("data/RezultateC{}_P{}.txt", i + 1, j + 1));
            for (int k = 0;k < contestants;++k) {
                int points;
                if (generateRandomNumber(100) <= chanceDisqualified)
                    points = -1;
                else {
                    if (generateRandomNumber(100) <= chanceNull)
                        points = 0;
                    else
                        points = generateRandomNumber(maxScore);
                }
                if (points)
                    cout << lastId + k << ' ' << points << '\n';
            }
            cout.close();
        }
        lastId += contestants;
    }
}