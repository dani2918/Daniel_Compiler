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
     BOOLCONST = 261,
     NOT = 262,
     AND = 263,
     OR = 264,
     RECORD = 265,
     STATIC = 266,
     INT = 267,
     BOOL = 268,
     CHAR = 269,
     IF = 270,
     ELSE = 271,
     WHILE = 272,
     RETURN = 273,
     BREAK = 274,
     OPT = 275,
     DOT = 276,
     ADDASS = 277,
     SUBASS = 278,
     MULASS = 279,
     DIVASS = 280,
     DEC = 281,
     INC = 282,
     EQ = 283,
     NOTEQ = 284,
     LESSEQ = 285,
     LT = 286,
     GRTEQ = 287,
     GT = 288,
     ASS = 289,
     MUL = 290,
     ADD = 291,
     SUB = 292,
     DIV = 293,
     MOD = 294,
     LPAREN = 295,
     RPAREN = 296,
     LBRAC = 297,
     RBRAC = 298,
     LCUR = 299,
     RCUR = 300,
     COMMA = 301,
     COL = 302,
     SEMI = 303,
     ERR = 304
   };
#endif
/* Tokens.  */
#define NUMCONST 258
#define CHARCONST 259
#define ID 260
#define BOOLCONST 261
#define NOT 262
#define AND 263
#define OR 264
#define RECORD 265
#define STATIC 266
#define INT 267
#define BOOL 268
#define CHAR 269
#define IF 270
#define ELSE 271
#define WHILE 272
#define RETURN 273
#define BREAK 274
#define OPT 275
#define DOT 276
#define ADDASS 277
#define SUBASS 278
#define MULASS 279
#define DIVASS 280
#define DEC 281
#define INC 282
#define EQ 283
#define NOTEQ 284
#define LESSEQ 285
#define LT 286
#define GRTEQ 287
#define GT 288
#define ASS 289
#define MUL 290
#define ADD 291
#define SUB 292
#define DIV 293
#define MOD 294
#define LPAREN 295
#define RPAREN 296
#define LBRAC 297
#define RBRAC 298
#define LCUR 299
#define RCUR 300
#define COMMA 301
#define COL 302
#define SEMI 303
#define ERR 304




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 48 "parser.y"
{
	TokenData *tokenData;
}
/* Line 1529 of yacc.c.  */
#line 151 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

