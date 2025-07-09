#include <bits/stdc++.h>
#include "tree.cpp"

using namespace std;

map<string, int> atoms;
BinaryTree<string> ids;

bool isId(const string& atom) {
    if (!isalpha(atom[0]))
        return false;
    for (auto x : atom)
        if (!isalnum(x))
            return false;
    return true;
}

bool isInt(string atom) {
    if (atom == "0")
        return true;
    if (atom[0] == '-')
        atom = atom.substr(1);
    if (atom[0] == '0')
        return false;
    for (auto x : atom)
        if (!isdigit(x))
            return false;
    return true;
}

bool isDouble(string atom) {
    if (isInt(atom))
        return true;
    auto it = atom.find('.');
    if (it != string::npos) {
        auto left = atom.substr(0, it);
        if (!isInt(left))
            return false;
        auto right = atom.substr(it + 1);
        for (auto x : right)
            if (!isdigit(x))
                return false;
        return true;
    }
    return false;
}

bool isString(string atom) {
    if (atom.front() != '"' || atom.back() != '"')
        return false;
    atom = atom.substr(1, atom.length() - 2);
    for (auto x : atom)
        if (!isalnum(x) && x != ':')
            return false;
    return true;
}

bool isConstant(string atom) {
    if (isInt(atom))
        return true;
    if (isDouble(atom))
        return true;
    if (isString(atom))
        return true;
    return false;

}

int findAtom(const string& atom) {
    if (atoms.count(atom))
        return atoms[atom];
    if (isId(atom))
        return 0;
    if (isConstant(atom))
        return 1;
    return -1;
}

int findID(const string& atom) {
    if (ids.find(atom) == -1) {
        ids.insert(atom);
    }
    return ids.find(atom);
}

void addAtom(const string& atom) {
    atoms[atom] = atoms.size() + 2;
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
    for (auto& [x, y] : atoms)
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
    ifstream cin("2.3.cpp");
    string line;
    int lineNumber = 0;
    vector<tuple<int, int, string>> errors;
    vector<tuple<string, int, int>> atoms;
    while (getline(cin, line)) {
        ++lineNumber;
        stringstream ss(line);
        string atom;
        int atomNumber = 0;
        while (ss >> atom) {
            ++atomNumber;
            int pos = findAtom(atom);
            int idPos = -1;
            if (pos != -1) {
                if (pos <= 1)
                    idPos = findID(atom);
                atoms.emplace_back(atom, pos, idPos);
            }
            else {
                errors.emplace_back(lineNumber, atomNumber, atom);
            }
        }
    }
    if (!errors.empty()) {
        cout << "ERRORS DETECTED!\n";
        for (auto& [lineNUmber, atomNumber, atom] : errors)
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