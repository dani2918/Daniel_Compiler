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
     ADDASS = 264,
     SUBASS = 265,
     MULASS = 266,
     DIVASS = 267,
     DEC = 268,
     INC = 269,
     EQ = 270,
     NOTEQ = 271,
     LESSEQ = 272,
     LT = 273,
     GRTEQ = 274,
     GT = 275,
     ASS = 276,
     MUL = 277,
     ADD = 278,
     SUB = 279,
     DIV = 280,
     MOD = 281,
     ERR = 282
   };
#endif
/* Tokens.  */
#define NUMCONST 258
#define CHARCONST 259
#define ID 260
#define NOT 261
#define AND 262
#define OR 263
#define ADDASS 264
#define SUBASS 265
#define MULASS 266
#define DIVASS 267
#define DEC 268
#define INC 269
#define EQ 270
#define NOTEQ 271
#define LESSEQ 272
#define LT 273
#define GRTEQ 274
#define GT 275
#define ASS 276
#define MUL 277
#define ADD 278
#define SUB 279
#define DIV 280
#define MOD 281
#define ERR 282




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 41 "parser.y"
{
	TokenData *tokenData;
}
/* Line 1529 of yacc.c.  */
#line 107 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

