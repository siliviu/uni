%{
	#include <bits/stdc++.h>
    #include "asm.h"
	using namespace std;

	// Declare stuff from Flex that Bison needs to know about:
	extern int yylex();
	extern int yyparse();
	extern FILE* yyin;
    extern int yylineno;
    extern vector<tuple<string, int, int>> atoms;
    extern void printAtom(ofstream& stream, const string& atom, int number, int number2 = -1, int number3 = -1);
    
    char dataSegment[100000];
	char codeSegment[100000];
    char buffer[2048];
    char filename[64] = "code.asm";

    int curTemp = 0;
	void declareTempVariable(char* name) {
		sprintf(name, "temp%d", curTemp++);
		sprintf(buffer, DECLARATION_INT_VARIABLE, name, "0");
		strcat(dataSegment, buffer);
	}

    void prepareAtoms();
    void printAtomTable();
    void printSymbolTable();
    void yyerror(const char* s);
%}

%code requires {
	struct attrib {
		char name[32];
		char code[512];
		int type;
	};
	typedef struct attrib attributes;
}

%union {
	int ival;
    char sval[32];
    attributes attr;
};


%token <ival> INT
%token <sval> ID
%type <attr> factor
%type <attr> term
%type <attr> expr
%token PLUS MINUS MULTIPLY EQUAL SEMICOLON
%token LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET
%token HASH INCLUDE IOSTREAM USING NAMESPACE STD TYPE_INT MAIN
%token INPUT OUTPUT INPUT_OPERATOR OUTPUT_OPERATOR

%%
program: HASH INCLUDE IOSTREAM USING NAMESPACE STD SEMICOLON TYPE_INT MAIN LEFT_BRACKET RIGHT_BRACKET body {
	FILE* out = fopen(filename, "w");
    fprintf(out, "%s\n", BEGIN_PROGRAM);
    fprintf(out, "%s\n", INITIAL_DATA_SEGMENT);
    fprintf(out, "%s\n", dataSegment); 
    fprintf(out, "%s\n", INITIAL_CODE_SEGMENT);
    fprintf(out, "%s\n", codeSegment);
    fprintf(out, "%s\n", EXIT_CODE);
}

body: LEFT_BRACE li RIGHT_BRACE
li: instr | instr li
instr: adecl | decl | assign | input | output

adecl: TYPE_INT ID EQUAL expr SEMICOLON {
    if($4.type == 0)
        sprintf(buffer, DECLARATION_INT_VARIABLE, $2, $4.name);
    else
        sprintf(buffer, DECLARATION_INT_VARIABLE, $2, "0");
    strcat(dataSegment, buffer);
    if ($4.type == 1)
        sprintf(buffer, ASSIGMENT, $4.name, $2);
    else
        sprintf(buffer, ASSIGMENT_CONSTANT, $4.name, $2);
    strcat(codeSegment, $4.code);
    strcat(codeSegment, buffer);
}

decl: TYPE_INT ID SEMICOLON {
    sprintf(buffer, DECLARATION_INT_VARIABLE, $2, "0");
    strcat(dataSegment, buffer);
}

assign: ID EQUAL expr SEMICOLON {
    if($3.type == 1)
        sprintf(buffer, ASSIGMENT, $3.name, $1);
    else
        sprintf(buffer, ASSIGMENT_CONSTANT, $3.name, $1);
    strcat(codeSegment, $3.code);
    strcat(codeSegment, buffer);
}

input: INPUT INPUT_OPERATOR ID SEMICOLON {
    sprintf(buffer, READ_STMT, $3);
	strcat(codeSegment, buffer);
}

output: OUTPUT OUTPUT_OPERATOR factor SEMICOLON {
    sprintf(buffer, WRITE_STMT, $3.name);
	strcat(codeSegment, buffer);
}
expr: expr PLUS term {
    declareTempVariable($$.name);
    if ($3.type == 1 && $1.type == 1)
        sprintf(buffer, ADDITION_V, $1.name, $3.name, $$.name);
    else if ($3.type == 0 && $1.type == 1)
        sprintf(buffer, ADDITION_C, $1.name, $3.name, $$.name);
    else if ($3.type == 1 && $1.type == 0)
        sprintf(buffer, ADDITION_C_V, $1.name, $3.name, $$.name);
    else if ($3.type == 0 && $1.type == 0)
        sprintf(buffer, ADDITION_C_C, $1.name, $3.name, $$.name);
    strcpy($$.code, $1.code);
    strcat($$.code, $3.code);
    strcat($$.code, buffer);
    $$.type = 1;
}
| expr MINUS term {
    declareTempVariable($$.name);
    if ($3.type == 1 && $1.type == 1)
        sprintf(buffer, MINUS_V, $1.name, $3.name, $$.name);
    else if ($3.type == 0 && $1.type == 1)
        sprintf(buffer, MINUS_C, $1.name, $3.name, $$.name);
    else if ($3.type == 1 && $1.type == 0)
        sprintf(buffer, MINUS_C_V, $1.name, $3.name, $$.name);
    else if ($3.type == 0 && $1.type == 0)
        sprintf(buffer, MINUS_C_C, $1.name, $3.name, $$.name);
    strcpy($$.code, $1.code);
    strcat($$.code, $3.code);
    strcat($$.code, buffer);
    $$.type = 1;
} | term {
    strcpy($$.name, $1.name);
    strcpy($$.code, $1.code);
    $$.type = $1.type;
}
term: term MULTIPLY factor {
    declareTempVariable($$.name);
    if ($3.type == 1 && $1.type == 1)
        sprintf(buffer, MULTIPLICATION_V, $1.name, $3.name, $$.name);
    else if ($3.type == 0 && $1.type == 1)
        sprintf(buffer, MULTIPLICATION_C, $1.name, $3.name, $$.name);
    else if ($3.type == 1 && $1.type == 0)
        sprintf(buffer, MULTIPLICATION_C_V, $1.name, $3.name, $$.name);
    else if ($3.type == 0 && $1.type == 0)
        sprintf(buffer, MULTIPLICATION_C_C, $1.name, $3.name, $$.name);
    strcat($$.code, $1.code);
    strcat($$.code, $3.code);
    strcat($$.code, buffer);
    $$.type = 1;
}
| factor {
    strcpy($$.name, $1.name);
    strcpy($$.code, $1.code);
    $$.type = $1.type;
}
factor: ID {
    strcpy($$.name, $1);
    strcpy($$.code, "");
    $$.type = 1;
}
| INT {
    strcpy($$.code, "");
    sprintf($$.name, "%d", $1);
    $$.type = 0;
}
%%

int main(int argc, char** argv) {
    prepareAtoms();
    printAtomTable();
	++argv, --argc;
	if (argc > 0) {
		yyin = fopen(argv[0], "r");
        strcpy(filename, argv[0]);
        strcpy(strstr(filename, ".cpp"), ".asm");
    }
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
