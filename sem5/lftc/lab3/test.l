%{
#include <bits/stdc++.h>
#include "tree.cpp"
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
    // Lab
    addAtom("cat timp");
    addAtom("executa");

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
%}

%option noyywrap 
DIGIT       [0-9]
POSDIGIT    [1-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
INT         0|{POSDIGIT}{DIGIT}*
DOUBLE      {DIGIT}+"."{DIGIT}*|{DIGIT}*"."{DIGIT}+

%%
"+"             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"-"             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"*"             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"/"             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"%"             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"<"             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
">"             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"=="            { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"="             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"!="            { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"<="            { atoms.emplace_back(yytext, atomsList[yytext], -1); }
">="            { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"<<"            { atoms.emplace_back(yytext, atomsList[yytext], -1); }
">>"            { atoms.emplace_back(yytext, atomsList[yytext], -1); }
","             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
";"             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
":"             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"{"             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"}"             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"("             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
")"             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"#"             { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"include"       { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"<iostream>"    { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"using"         { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"namespace"     { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"std"           { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"int"           { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"double"        { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"if"            { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"while"         { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"return"        { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"cin"           { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"cout"          { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"struct"        { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"switch"        { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"case"          { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"break"         { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"cat timp"         { atoms.emplace_back(yytext, atomsList[yytext], -1); }
"executa"         { atoms.emplace_back(yytext, atomsList[yytext], -1); }

{ID}            { atoms.emplace_back(yytext, 0, findID(yytext)); }
{INT}|{DOUBLE}           { atoms.emplace_back(yytext, 1, findID(yytext)); }

\n { yylineno++;}
[ \t]+        {  }
[|&$.^ \t\n] { errors.emplace_back(yylineno, 0, yytext);}
%%

int main(int argc,char** argv) {
    prepareAtoms();
    printAtomTable();
    string line;
    ++argv, --argc;
	if (argc > 0)
		yyin = fopen(argv[0], "r");
	else
		yyin = stdin;
	yylex();
    
    yylex();
    if (!errors.empty()) {
        cout << "ERRORS DETECTED!\n";
        for (auto& [lineNumber, atomNumber, atom] : errors)
            cout << "Line: " << lineNumber << ", Atom: " << atom << '\n';
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