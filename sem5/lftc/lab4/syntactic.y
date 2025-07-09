%{
	#include <bits/stdc++.h>
	using namespace std;

	// Declare stuff from Flex that Bison needs to know about:
	extern int yylex();
	extern int yyparse();
	extern FILE* yyin;
    extern int yylineno;
    extern vector<tuple<string, int, int>> atoms;
    extern void printAtom(ofstream& stream, const string& atom, int number, int number2 = -1, int number3 = -1);
    
    void prepareAtoms();
    void printAtomTable();
    void printSymbolTable();
    void yyerror(const char* s);
%}

%union {
	int ival;
	double dval; 
};


%token <ival> INT
%token <dval> DOUBLE 
%token ID ARITHMETIC_OPERATOR_1 ARITHMETIC_OPERATOR_2 RELATION_OPERATOR ASSIGNMENT_OPERATOR INPUT_OPERATOR OUTPUT_OPERATOR
%token COMMA SEMICOLON COLON LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET
%token HASH INCLUDE LIBRARY KEYWORD_USING KEYWORD_NAMESPACE NAMESPACE TYPE
%token IF WHILE RETURN INPUT OUTPUT STRUCT SWITCH CASE BREAK CATTIMP EXECUTA

%left ARITHMETIC_OPERATOR_1
%left ARITHMETIC_OPERATOR_2

%%
program: incl ns fct

incl: HASH INCLUDE LIBRARY
ns: KEYWORD_USING KEYWORD_NAMESPACE NAMESPACE SEMICOLON
fct: TYPE ID LEFT_BRACKET typelist RIGHT_BRACKET ic
typelist: | TYPE ID | TYPE ID COMMA typelist

ic: LEFT_BRACE li RIGHT_BRACE
li: instr | instr li
instr: adecl | decl | op | instr_cond | instr_cicl | instr_switch | decl_struct | return

adecl: TYPE la SEMICOLON
la: ID ASSIGNMENT_OPERATOR expr | ID ASSIGNMENT_OPERATOR expr COMMA la 
decl: TYPE ID SEMICOLON 

op: atr | intrare | iesire
atr: ID ASSIGNMENT_OPERATOR expr SEMICOLON
intrare: INPUT INPUT_OPERATOR ID SEMICOLON
iesire: OUTPUT OUTPUT_OPERATOR expr SEMICOLON
expr: ID | INT | DOUBLE |
                expr ARITHMETIC_OPERATOR_1 expr |
                expr ARITHMETIC_OPERATOR_2 expr
instr_cond: IF LEFT_BRACKET cond RIGHT_BRACKET ic
instr_cicl: WHILE LEFT_BRACKET cond RIGHT_BRACKET ic

cond: expr RELATION_OPERATOR expr
decl_struct: STRUCT ID LEFT_BRACE decl RIGHT_BRACE SEMICOLON
instr_switch: SWITCH LEFT_BRACKET expr RIGHT_BRACKET LEFT_BRACE CASE expr COLON li BREAK RIGHT_BRACE SEMICOLON
return: RETURN expr SEMICOLON
%%

int main(int argc, char** argv) {
    prepareAtoms();
    printAtomTable();
	++argv, --argc;
	if (argc > 0)
		yyin = fopen(argv[0], "r");
	else
		yyin = stdin;
    if (yyparse() == 0) {
        cout << "Syntactic Parsing completed successfully!" << endl;
        printSymbolTable();
        ofstream ccout("atoms.txt");
        ccout << "FIP\n";
        for (auto& [atom, pos, idPos] : atoms)
            printAtom(ccout, atom, pos, idPos);
    }
}

void yyerror(const char* s) {
    cout << "Error: " << s << " at line " << yylineno << endl;
    exit(1);
}
