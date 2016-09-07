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
     NOT = 261,
     AND = 262,
     OR = 263,
     RECORD = 264,
     STATIC = 265,
     INT = 266,
     BOOL = 267,
     CHAR = 268,
     PTR = 269,
     ADDASS = 270,
     SUBASS = 271,
     MULASS = 272,
     DIVASS = 273,
     DEC = 274,
     INC = 275,
     EQ = 276,
     NOTEQ = 277,
     LESSEQ = 278,
     LT = 279,
     GRTEQ = 280,
     GT = 281,
     ASS = 282,
     MUL = 283,
     ADD = 284,
     SUB = 285,
     DIV = 286,
     MOD = 287,
     ERR = 288
   };
#endif
/* Tokens.  */
#define NUMCONST 258
#define CHARCONST 259
#define ID 260
#define NOT 261
#define AND 262
#define OR 263
#define RECORD 264
#define STATIC 265
#define INT 266
#define BOOL 267
#define CHAR 268
#define PTR 269
#define ADDASS 270
#define SUBASS 271
#define MULASS 272
#define DIVASS 273
#define DEC 274
#define INC 275
#define EQ 276
#define NOTEQ 277
#define LESSEQ 278
#define LT 279
#define GRTEQ 280
#define GT 281
#define ASS 282
#define MUL 283
#define ADD 284
#define SUB 285
#define DIV 286
#define MOD 287
#define ERR 288




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 42 "parser.y"
{
	TokenData *tokenData;
}
/* Line 1529 of yacc.c.  */
#line 119 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

