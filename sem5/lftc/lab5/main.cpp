#include <bits/stdc++.h>

using namespace std;

const char EPSILON = '@';
const char END = '$';

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

    map<char, set<char>> first;
    for (auto [left, right] : prods) {
        if (right.empty())
            first[left].emplace(EPSILON);
        else if (!isupper(right[0])) {
            first[left].emplace(right[0]);
        }
    }
    auto calculateFirst = [&](vector<char> input) {
        if (input.empty())
            return set{ EPSILON };
        set<char> ans;
        for (auto cur : input) {
            if (!isupper(cur)) {
                ans.emplace(cur);
                break;
            }
            ans.insert(first[cur].begin(), first[cur].end());
            if (!ans.count(EPSILON))
                break;
            if (cur != input.back())
                ans.erase(EPSILON);
        }
        return ans;
        };

    while (true) {
        map<char, set<char>> newFirst;
        for (auto [left, right] : prods)
            newFirst[left].merge(calculateFirst(right));
        if (first == newFirst)
            break;
        first = newFirst;
    }
    cout << "FIRST\n";
    for (auto x : neterm) {
        cout << x << " | ";
        for (auto y : first[x])
            cout << y << ' ';
        cout << '\n';
    }

    map<char, set<char>> follow;
    follow[start] = { END };
    while (true) {
        map newFollow = follow;
        for (auto [left, right] : prods) {
            for (auto it = right.begin();(it = find_if(it, right.end(), [&](char x) {return isupper(x);})) != right.end();) {
                auto cur = *it;
                auto first = calculateFirst(vector<char>(++it, right.end()));
                if (first.contains(EPSILON)) {
                    first.erase(EPSILON);
                    if (follow.count(left))
                        newFollow[cur].insert(follow[left].begin(), follow[left].end());
                }
                newFollow[cur].merge(first);
            }
        }
        if (follow == newFollow)
            break;
        follow = newFollow;
    }
    cout << "FOLLOW\n";
    for (auto x : neterm) {
        cout << x << " | ";
        for (auto y : follow[x])
            cout << y << ' ';
        cout << '\n';
    }

    map<pair<char, char>, int> m;
    for (auto [idx, prod] : views::enumerate(prods)) {
        auto [left, right] = prod;
        cout << left << ' ';
        for (auto x : right)
            cout << x << ' ';
        cout << '\n';
        auto first = calculateFirst(right);
        if (first.contains(EPSILON)) {
            first.erase(EPSILON);
            for (auto symbol : follow[left]) {
                if (m.count({ left,symbol })) {
                    cout << symbol << '\n';
                    cout << "TABLE CONFLICT" << '\n' << "GRAMMAR NOT LL(1)";
                    exit(0);
                }
                m[{left, symbol}] = idx;
            }
        }
        for (auto symbol : first) {
            if (m.count({ left,symbol })) {
                cout << symbol << '\n';
                cout << "TABLE CONFLICT" << '\n' << "GRAMMAR NOT LL(1)";
                exit(0);
            }
            m[{left, symbol}] = idx;
        }
    }

    string expr;
    cin >> expr;
    expr += END;
    reverse(expr.begin(), expr.end());
    stack<char> input(expr.begin(), expr.end()), stack;
    vector<int> ans;
    stack.emplace(END);
    stack.emplace(start);
    while (true) {
        if (input.top() == stack.top()) {
            if (input.top() == END)
                break;
            input.pop();
            stack.pop();
            continue;
        }
        if (!m.count({ stack.top(),input.top() })) {
            cout << "NOT ACCEPTED\n";
            exit(0);
        }
        int index = m[{stack.top(), input.top()}];
        stack.pop();
        ans.emplace_back(index);
        for (auto x : views::reverse(prods[index].second))
            stack.push(x);
    }
    cout << "ACCEPTED" << '\n';
    for (auto x : ans)
        cout << x + 1 << ' ';
}