%{
#include <bits/stdc++.h>
#include "tree.cpp"
#include "syntactic.tab.h"
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
    // Lab
    addAtom("switch");
    addAtom("case");
    addAtom("break");
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

%%
"+"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return PLUS;}
"-"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return MINUS;}
"*"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return MULTIPLY;}
"="             { atoms.emplace_back(yytext, atomsList[yytext], -1); return EQUAL;}
";"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return SEMICOLON;}
"{"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return LEFT_BRACE;}
"}"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return RIGHT_BRACE;}
"("             { atoms.emplace_back(yytext, atomsList[yytext], -1); return LEFT_BRACKET;}
")"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return RIGHT_BRACKET;}
"#"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return HASH;}
"include"       { atoms.emplace_back(yytext, atomsList[yytext], -1); return INCLUDE;}
"<iostream>"    { atoms.emplace_back(yytext, atomsList[yytext], -1); return IOSTREAM;}
"using"         { atoms.emplace_back(yytext, atomsList[yytext], -1); return USING;}
"namespace"     { atoms.emplace_back(yytext, atomsList[yytext], -1); return NAMESPACE;}
"std"           { atoms.emplace_back(yytext, atomsList[yytext], -1); return STD;}
"int"           { atoms.emplace_back(yytext, atomsList[yytext], -1); return TYPE_INT;}
"main"           { atoms.emplace_back(yytext, atomsList[yytext], -1); return MAIN;}
"cin"           { atoms.emplace_back(yytext, atomsList[yytext], -1); return INPUT;}
">>"           { atoms.emplace_back(yytext, atomsList[yytext], -1); return INPUT_OPERATOR;}
"cout"          { atoms.emplace_back(yytext, atomsList[yytext], -1); return OUTPUT;}
"<<"           { atoms.emplace_back(yytext, atomsList[yytext], -1); return OUTPUT_OPERATOR;}

{ID}            {   
    atoms.emplace_back(yytext, 0, findID(yytext)); 
    strcpy(yylval.sval, yytext);
    return ID;
}
{INT}           {
    atoms.emplace_back(yytext, 1, findID(yytext));
    yylval.ival = atoi(yytext);
    return INT;
    }

\n { yylineno++;}
[ \t]+        {  }
[|&$.^ \t\n] { errors.emplace_back(yylineno, 0, yytext); cout << "ERROR: " << yylineno << ' ' << yytext << '\n'; exit(0);}
%%
