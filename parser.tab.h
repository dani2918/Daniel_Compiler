/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMCONST = 258,
     CHARCONST = 259,
     ID = 260,
     RECTYPE = 261,
     BOOLCONST = 262,
     NOT = 263,
     AND = 264,
     OR = 265,
     RECORD = 266,
     STATIC = 267,
     INT = 268,
     BOOL = 269,
     CHAR = 270,
     IF = 271,
     ELSE = 272,
     WHILE = 273,
     RETURN = 274,
     BREAK = 275,
     RAND = 276,
     DOT = 277,
     ADDASS = 278,
     SUBASS = 279,
     MULASS = 280,
     DIVASS = 281,
     DEC = 282,
     INC = 283,
     EQ = 284,
     NOTEQ = 285,
     LESSEQ = 286,
     LT = 287,
     GRTEQ = 288,
     GT = 289,
     ASS = 290,
     MUL = 291,
     ADD = 292,
     SUB = 293,
     DIV = 294,
     MOD = 295,
     LPAREN = 296,
     RPAREN = 297,
     LBRAC = 298,
     RBRAC = 299,
     LCUR = 300,
     RCUR = 301,
     COMMA = 302,
     COL = 303,
     SEMI = 304,
     ERR = 305
   };
#endif
/* Tokens.  */
#define NUMCONST 258
#define CHARCONST 259
#define ID 260
#define RECTYPE 261
#define BOOLCONST 262
#define NOT 263
#define AND 264
#define OR 265
#define RECORD 266
#define STATIC 267
#define INT 268
#define BOOL 269
#define CHAR 270
#define IF 271
#define ELSE 272
#define WHILE 273
#define RETURN 274
#define BREAK 275
#define RAND 276
#define DOT 277
#define ADDASS 278
#define SUBASS 279
#define MULASS 280
#define DIVASS 281
#define DEC 282
#define INC 283
#define EQ 284
#define NOTEQ 285
#define LESSEQ 286
#define LT 287
#define GRTEQ 288
#define GT 289
#define ASS 290
#define MUL 291
#define ADD 292
#define SUB 293
#define DIV 294
#define MOD 295
#define LPAREN 296
#define RPAREN 297
#define LBRAC 298
#define RBRAC 299
#define LCUR 300
#define RCUR 301
#define COMMA 302
#define COL 303
#define SEMI 304
#define ERR 305




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 74 "parser.y"
{
	TokenData *tokenData;

#line 79 "parser.y"

	TreeNode *treeNode;

#line 84 "parser.y"

	ExpType expType;
	int number; 
	TokenData * td;
	TreeNode * t;
	char * name;


#line 94 "parser.y"

	char * c;
}
/* Line 1529 of yacc.c.  */
#line 170 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

