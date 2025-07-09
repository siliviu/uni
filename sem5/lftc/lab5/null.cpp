#include <bits/stdc++.h>

using namespace std;

const char EPSILON = '@';

int main(int argc, char** argv) {
    assert(argc - 1 == 1);

    ifstream file(argv[1]);

    string line;
    set<char> V;
    char start = 0;
    set<char> neterm;
    vector<pair<char, vector<char>>> prods;
    while (getline(file, line)) {
        stringstream ss(line);
        char chr;
        bool first = true;
        string firstNeterm;
        pair<char, vector<char>> curProd;
        while (ss >> chr) {
            if (isupper(chr)) {
                if (first) {
                    if (start == 0)
                        start = chr;
                    neterm.emplace(chr);
                    curProd.first = chr;
                }
                else {
                    curProd.second.emplace_back(chr);
                }
                first = false;
            }
            else if (chr != '-' && chr != '>') {
                if (chr != EPSILON) {
                    curProd.second.emplace_back(chr);
                }
                else {
                    V.emplace(curProd.first);
                }
            }
        }
        prods.emplace_back(curProd);
    }

    while (true) {
        set newV = V;
        for (auto [left, right] : prods) {
            bool ok = true;
            for (auto x : right)
                if (!V.count(x)) {
                    ok = false;
                    break;
                }
            if (ok)
                newV.emplace(left);
        }
        if (newV == V)
            break;
        V = newV;
    }

    cout << V.size() << '\n';
    for (auto x : V)
        cout << x << ' ';
}