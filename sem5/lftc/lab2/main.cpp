#include <bits/stdc++.h>
#include "fsm.cpp"

using namespace std;

int main() {
        vector<char> alphabet;
        vector<string> states;
        string initialState;
        vector<string> finalStates;
        vector<tuple<string, string, char>> transitions;
        {
            ifstream cin("aut2.txt");
            string alphabetLine;
            getline(cin, alphabetLine);
            cerr << alphabetLine << '\n';
            stringstream ss(alphabetLine);
            char symbol;
            while (ss >> symbol)
                alphabet.emplace_back(symbol);
            string statesLine;
            getline(cin, statesLine);
            ss = stringstream(statesLine);
            string state;
            while (ss >> state)
                states.emplace_back(state);
            cin >> initialState;
            string finalStatesLine;
            getline(cin, finalStatesLine);
            getline(cin, finalStatesLine);
            ss = stringstream(finalStatesLine);
            string finalState;
            while (ss >> finalState)
                finalStates.emplace_back(finalState);
            string from, to;
            while (cin >> from >> to >> symbol)
                transitions.emplace_back(from, to, symbol);
        }
        FSM fsm(alphabet, states, initialState, finalStates, transitions);
    cout << R"(Menu:
    1. See alphabet
    2. See all states
    3. See all final states
    4. See transitions
    5. Check if input is accepted
    6. Check longest accepted prefix from input
    )";
    while (1) {
        int number;
        cin >> number;
        if (number == 1) {
            for (auto& symbol : fsm.getAlphabet())
                cout << symbol << ' ';
            cout << '\n';
        }
        else if (number == 2) {
            for (auto& state : fsm.getStates())
                cout << state << ' ';
            cout << '\n';
        }
        else if (number == 3) {
            for (auto& state : fsm.getFinalStates())
                cout << state << ' ';
            cout << '\n';
        }
        else if (number == 4) {
            for (auto& [from, to, symbol] : fsm.getTransitions())
                cout << from << ' ' << to << ' ' << symbol << '\n';
        }
        else if (number == 5 || number == 6) {
            string input;
            cin >> input;
            if (input == "EPSILON")
                input = "";
            std::vector<char> chars(input.begin(), input.end());
            if (!fsm.isDeterministic())
                cout << "Not deterministic\n";
            else {
                if (number == 5)
                    cout << (fsm.isAccepted(chars) ? "Accepted" : "Not accepted") << '\n';
                else {
                    vector<char> ans = fsm.getLongestAccepted(chars);
                    if (!fsm.isAccepted(ans))
                        cout << "No prefix accepted\n";
                    else {
                        string ans2 = string(ans.begin(), ans.end());
                        cout << (ans2 == "" ? "EPSILON" : ans2) << '\n';
                    }
                }
            }
        }
    }
}