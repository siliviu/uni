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
DOUBLE      {DIGIT}+"."{DIGIT}*|{DIGIT}*"."{DIGIT}+

%%
"+"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return ARITHMETIC_OPERATOR_1;}
"-"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return ARITHMETIC_OPERATOR_1;}
"*"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return ARITHMETIC_OPERATOR_2;}
"/"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return ARITHMETIC_OPERATOR_2;}
"%"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return ARITHMETIC_OPERATOR_2;}
"<"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return RELATION_OPERATOR;}
">"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return RELATION_OPERATOR;}
"=="            { atoms.emplace_back(yytext, atomsList[yytext], -1); return RELATION_OPERATOR;}
"="             { atoms.emplace_back(yytext, atomsList[yytext], -1); return ASSIGNMENT_OPERATOR;}
"!="            { atoms.emplace_back(yytext, atomsList[yytext], -1); return RELATION_OPERATOR;}
"<="            { atoms.emplace_back(yytext, atomsList[yytext], -1); return RELATION_OPERATOR;}
">="            { atoms.emplace_back(yytext, atomsList[yytext], -1); return RELATION_OPERATOR;}
"<<"            { atoms.emplace_back(yytext, atomsList[yytext], -1); return OUTPUT_OPERATOR;}
">>"            { atoms.emplace_back(yytext, atomsList[yytext], -1); return INPUT_OPERATOR;}
","             { atoms.emplace_back(yytext, atomsList[yytext], -1); return COMMA;}
";"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return SEMICOLON;}
":"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return COLON;}
"{"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return LEFT_BRACE;}
"}"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return RIGHT_BRACE;}
"("             { atoms.emplace_back(yytext, atomsList[yytext], -1); return LEFT_BRACKET;}
")"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return RIGHT_BRACKET;}
"#"             { atoms.emplace_back(yytext, atomsList[yytext], -1); return HASH;}
"include"       { atoms.emplace_back(yytext, atomsList[yytext], -1); return INCLUDE;}
"<iostream>"    { atoms.emplace_back(yytext, atomsList[yytext], -1); return LIBRARY;}
"using"         { atoms.emplace_back(yytext, atomsList[yytext], -1); return KEYWORD_USING;}
"namespace"     { atoms.emplace_back(yytext, atomsList[yytext], -1); return KEYWORD_NAMESPACE;}
"std"           { atoms.emplace_back(yytext, atomsList[yytext], -1); return NAMESPACE;}
"int"           { atoms.emplace_back(yytext, atomsList[yytext], -1); return TYPE;}
"double"        { atoms.emplace_back(yytext, atomsList[yytext], -1); return TYPE;}
"if"            { atoms.emplace_back(yytext, atomsList[yytext], -1); return IF;}
"while"         { atoms.emplace_back(yytext, atomsList[yytext], -1); return WHILE;}
"return"        { atoms.emplace_back(yytext, atomsList[yytext], -1); return RETURN;}
"cin"           { atoms.emplace_back(yytext, atomsList[yytext], -1); return INPUT;}
"cout"          { atoms.emplace_back(yytext, atomsList[yytext], -1); return OUTPUT;}
"struct"        { atoms.emplace_back(yytext, atomsList[yytext], -1); return STRUCT;}
"switch"        { atoms.emplace_back(yytext, atomsList[yytext], -1); return SWITCH;}
"case"          { atoms.emplace_back(yytext, atomsList[yytext], -1); return CASE;}
"break"         { atoms.emplace_back(yytext, atomsList[yytext], -1); return BREAK;}
"cat timp"         { atoms.emplace_back(yytext, atomsList[yytext], -1); return CATTIMP;}
"executa"         { atoms.emplace_back(yytext, atomsList[yytext], -1); return EXECUTA;}

{ID}            { atoms.emplace_back(yytext, 0, findID(yytext)); return ID;}
{INT}           { atoms.emplace_back(yytext, 1, findID(yytext)); return INT;}
{DOUBLE}           { atoms.emplace_back(yytext, 1, findID(yytext)); return  DOUBLE;}

\n { yylineno++;}
[ \t]+        {  }
[|&$.^ \t\n] { errors.emplace_back(yylineno, 0, yytext); cout << "ERROR: " << yylineno << ' ' << yytext << '\n'; exit(0);}
%%
