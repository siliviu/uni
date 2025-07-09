#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("input.txt");
    string line;
    string start = "";
    set<string> neterm;
    set<string> term;
    vector<string> prod;
    while (getline(cin, line)) {
        stringstream ss(line);
        char chr;
        while (ss >> chr) {
            if (isupper(chr)) {
                if (start == "")
                    start = chr;
                neterm.emplace(std::string(1, chr));
            }
            else if (chr != '-' && chr != '>' && chr!='e') {
                term.emplace(std::string(1, chr));
            }
        }
        prod.emplace_back(line);
    }
    cout << "Start: " << start << '\n';
    cout << "Neterminale: ";
    for (auto x : neterm)
        cout << x << " ";
    cout << '\n';
    cout << "Terminale: ";
    for (auto x : term)
        cout << x << " ";
    cout << '\n';
    cout << "Productii: \n";
    for (auto x : prod)
        cout << x << '\n';
}