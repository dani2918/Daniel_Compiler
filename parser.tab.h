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
     IF = 269,
     ELSE = 270,
     WHILE = 271,
     RETURN = 272,
     BREAK = 273,
     PTR = 274,
     ADDASS = 275,
     SUBASS = 276,
     MULASS = 277,
     DIVASS = 278,
     DEC = 279,
     INC = 280,
     EQ = 281,
     NOTEQ = 282,
     LESSEQ = 283,
     LT = 284,
     GRTEQ = 285,
     GT = 286,
     ASS = 287,
     MUL = 288,
     ADD = 289,
     SUB = 290,
     DIV = 291,
     MOD = 292,
     ERR = 293
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
#define IF 269
#define ELSE 270
#define WHILE 271
#define RETURN 272
#define BREAK 273
#define PTR 274
#define ADDASS 275
#define SUBASS 276
#define MULASS 277
#define DIVASS 278
#define DEC 279
#define INC 280
#define EQ 281
#define NOTEQ 282
#define LESSEQ 283
#define LT 284
#define GRTEQ 285
#define GT 286
#define ASS 287
#define MUL 288
#define ADD 289
#define SUB 290
#define DIV 291
#define MOD 292
#define ERR 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 42 "parser.y"
{
	TokenData *tokenData;
}
/* Line 1529 of yacc.c.  */
#line 129 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

