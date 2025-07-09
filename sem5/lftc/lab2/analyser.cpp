#include <bits/stdc++.h>
#include "tree.cpp"
#include "fsm.cpp"

using namespace std;

map<string, int, greater<string>> atomsList;
BinaryTree<string> ids;
vector<tuple<int, int, string>> errors;
vector<tuple<string, int, int>> atoms;

int findID(const string& atom) {
    if (ids.find(atom) == -1) {
        ids.insert(atom);
    }
    return ids.find(atom);
}

void addAtom(const string& atom) {
    atomsList[atom] = atomsList.size() + 2;
}

void prepareAtoms() {
    // Operators
    addAtom("+");
    addAtom("-");
    addAtom("*");
    addAtom("/");
    addAtom("%");
    addAtom("<");
    addAtom(">");
    addAtom("=");
    addAtom("==");
    addAtom("!=");
    addAtom("<=");
    addAtom(">=");
    addAtom("<<");
    addAtom(">>");
    // Delimitators
    addAtom(",");
    addAtom(";");
    addAtom(":");
    addAtom("{");
    addAtom("}");
    addAtom("(");
    addAtom(")");
    // Keywords
    addAtom("#");
    addAtom("include");
    addAtom("<iostream>");
    addAtom("using");
    addAtom("namespace");
    addAtom("std");
    addAtom("int");
    addAtom("double");
    addAtom("if");
    addAtom("while");
    addAtom("return");
    addAtom("cin");
    addAtom("cout");
    addAtom("struct");
    addAtom("switch");
    addAtom("case");
    addAtom("break");
}

FSM<> readAutomata(string file) {
    vector<char> alphabet;
    vector<string> states;
    string initialState;
    vector<string> finalStates;
    vector<tuple<string, string, char>> transitions;
    ifstream cin(file);
    string alphabetLine;
    getline(cin, alphabetLine);
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
    return FSM(alphabet, states, initialState, finalStates, transitions);
}

string tryId(string s) {
    static FSM fsm = readAutomata("id.txt");
    auto match = fsm.getLongestAccepted(vector<char>(s.begin(), s.end()));
    if (match.size() == 0)
        return string();
    return string(match.begin(), match.end());
}

string tryInt(string s) {
    static FSM fsm = readAutomata("int.txt");
    auto match = fsm.getLongestAccepted(vector<char>(s.begin(), s.end()));
    if (match.size() == 0)
        return string();
    return string(match.begin(), match.end());
}

string tryDouble(string s) {
    static FSM fsm = readAutomata("double.txt");
    auto match = fsm.getLongestAccepted(vector<char>(s.begin(), s.end()));
    if (match.size() == 0)
        return string();
    return string(match.begin(), match.end());
}

void printAtom(ofstream& stream, const string& atom, int number, int number2 = -1, int number3 = -1) {
    stream << left << setw(16) << atom;
    stream << " | ";
    stream << left << setw(4) << number;
    stream << " | ";
    if (number2 != -1)
        stream << left << setw(4) << number2;
    if (number3 != -1) {
        stream << " | ";
        stream << left << setw(4) << number3;
    }
    stream << '\n';

}

void printAtomTable() {
    ofstream cout("table.txt");
    cout << "ATOM TABLE: \n";
    printAtom(cout, "ID", 0);
    printAtom(cout, "CONST", 1);
    vector<pair<int, string>> list;
    for (auto& [x, y] : atomsList)
        list.emplace_back(y, x);
    sort(list.begin(), list.end());
    for (auto& [y, x] : list)
        printAtom(cout, x, y);
    cout << '\n';
}

void printSymbolTable() {
    ofstream cout("symbols.txt");
    cout << "SYMBOL TABLE: \n";
    int n = ids.getSize();
    for (int i = 0;i < n;++i) {
        auto node = ids.getNode(i);
        printAtom(cout, node.val, i, node.left, node.right);
    }
    cout << '\n';
}

int main() {
    prepareAtoms();
    printAtomTable();
    ifstream cin("2.1.cpp");
    string line;
    int lineNumber = 0;
    vector<tuple<int, int, string>> errors;
    vector<tuple<string, int, int>> atoms;
    while (getline(cin, line)) {
        ++lineNumber;
        int atomNumber = 0;
        while (!line.empty()) {
            if (isspace(line[0])) {
                line = line.substr(1);
                continue;
            }
            ++atomNumber;
            bool foundAtom = false;
            for (auto& [atom, pos] : atomsList)
                if (line.starts_with(atom)) {
                    atoms.emplace_back(atom, pos, -1);
                    line = line.substr(atom.length());
                    foundAtom = true;
                    break;
                }
            if (foundAtom)
                continue;
            for (auto func : { tryId, tryDouble,tryInt }) {
                string prefix = func(line);
                if (!prefix.empty()) {
                    atoms.emplace_back(prefix, func == tryId ? 0 : 1, findID(prefix));
                    line = line.substr(prefix.length());
                    foundAtom = true;
                    break;
                }
            }
            if (foundAtom)
                continue;
            errors.emplace_back(lineNumber, atomNumber, line);
            break;
        }
    }
    if (!errors.empty()) {
        cout << "ERRORS DETECTED!\n";
        for (auto& [lineNumber, atomNumber, atom] : errors)
            cout << "Line: " << lineNumber << ", Symbol Number: " << atomNumber << ", Atom: " << atom << '\n';
    }
    else {
        printSymbolTable();
        cout << "NO ERRORS\n";
        ofstream ccout("atoms.txt");
        ccout << "FIP\n";
        for (auto& [atom, pos, idPos] : atoms)
            printAtom(ccout, atom, pos, idPos);
    }
}