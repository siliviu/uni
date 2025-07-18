/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SYNTACTIC_TAB_H_INCLUDED
# define YY_YY_SYNTACTIC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    DOUBLE = 259,                  /* DOUBLE  */
    ID = 260,                      /* ID  */
    ARITHMETIC_OPERATOR_1 = 261,   /* ARITHMETIC_OPERATOR_1  */
    ARITHMETIC_OPERATOR_2 = 262,   /* ARITHMETIC_OPERATOR_2  */
    RELATION_OPERATOR = 263,       /* RELATION_OPERATOR  */
    ASSIGNMENT_OPERATOR = 264,     /* ASSIGNMENT_OPERATOR  */
    INPUT_OPERATOR = 265,          /* INPUT_OPERATOR  */
    OUTPUT_OPERATOR = 266,         /* OUTPUT_OPERATOR  */
    COMMA = 267,                   /* COMMA  */
    SEMICOLON = 268,               /* SEMICOLON  */
    COLON = 269,                   /* COLON  */
    LEFT_BRACE = 270,              /* LEFT_BRACE  */
    RIGHT_BRACE = 271,             /* RIGHT_BRACE  */
    LEFT_BRACKET = 272,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 273,           /* RIGHT_BRACKET  */
    HASH = 274,                    /* HASH  */
    INCLUDE = 275,                 /* INCLUDE  */
    LIBRARY = 276,                 /* LIBRARY  */
    KEYWORD_USING = 277,           /* KEYWORD_USING  */
    KEYWORD_NAMESPACE = 278,       /* KEYWORD_NAMESPACE  */
    NAMESPACE = 279,               /* NAMESPACE  */
    TYPE = 280,                    /* TYPE  */
    IF = 281,                      /* IF  */
    WHILE = 282,                   /* WHILE  */
    RETURN = 283,                  /* RETURN  */
    INPUT = 284,                   /* INPUT  */
    OUTPUT = 285,                  /* OUTPUT  */
    STRUCT = 286,                  /* STRUCT  */
    SWITCH = 287,                  /* SWITCH  */
    CASE = 288,                    /* CASE  */
    BREAK = 289,                   /* BREAK  */
    CATTIMP = 290,                 /* CATTIMP  */
    EXECUTA = 291                  /* EXECUTA  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "syntactic.y"

	int ival;
	double dval; 

#line 105 "syntactic.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SYNTACTIC_TAB_H_INCLUDED  */
