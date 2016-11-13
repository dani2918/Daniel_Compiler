/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 2 "parser.y"

 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include "globals.h"
 #include "scanType.h"
 #include "syntaxTree.h"
 #include "symbolTable.h"
 #include "printtree.h"
 #include "semantic.h"
 #include "yyerror.h"

 #include "parser.tab.h"

#define YYERROR_VERBOSE 1

 extern int yylex();
 extern int yyparse();
 extern FILE *yyin;
 extern int lineno;
 extern SymbolTable symTab;
 


 SymbolTable finalSymTab;
 

 //Like the TreeNode from tiny.y
 static TreeNode * savedTree;
 static TreeNode * setupTree;
 int savedLineNo;

 ExpType storedType;
 bool isStatic = false;
 TreeNode * nullablePlaceholder;

// To track epsilon productions
 int firstTimeThrough = 0;


//void yyerror(const char *errMsg)
//{
 //	printf("ERROR(%d): %s\n", lineno, errMsg);

//}

void printToken(int lineno, char* tokenString)
{
	printf("Line %d Token: %s\n", lineno, tokenString);
}

void printErrToken(int lineno, char* tokenString)
{
	printf("ERROR(%d): Invalid or misplaced input character: \"%s\"\n", lineno, tokenString);
}


 

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 80 "parser.y"
{
	TokenData *tokenData;

#line 85 "parser.y"

	TreeNode *treeNode;

#line 90 "parser.y"

	ExpType expType;
	int number; 
	TokenData * td;
	TreeNode * t;
	char * name;


#line 100 "parser.y"

	char * c;
}
/* Line 193 of yacc.c.  */
#line 276 "parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 289 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   821

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  166
/* YYNRULES -- Number of states.  */
#define YYNSTATES  262

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    18,
      24,    28,    32,    36,    40,    44,    48,    52,    56,    58,
      60,    62,    66,    70,    74,    76,    81,    85,    88,    91,
      93,    95,    97,    99,   101,   103,   110,   113,   118,   125,
     131,   135,   141,   143,   144,   148,   152,   154,   156,   159,
     162,   166,   170,   172,   174,   176,   180,   183,   185,   187,
     189,   191,   193,   195,   200,   205,   210,   213,   214,   217,
     218,   221,   223,   225,   227,   235,   242,   248,   253,   259,
     267,   271,   278,   284,   289,   295,   298,   300,   302,   308,
     314,   322,   325,   330,   337,   343,   348,   354,   357,   361,
     364,   368,   372,   376,   380,   384,   388,   391,   394,   397,
     400,   402,   406,   410,   412,   416,   420,   422,   425,   428,
     430,   434,   438,   442,   444,   446,   448,   450,   452,   454,
     456,   460,   464,   466,   468,   470,   474,   478,   480,   482,
     484,   486,   489,   492,   494,   496,   498,   500,   502,   504,
     506,   511,   515,   519,   522,   525,   527,   529,   534,   537,
     539,   540,   544,   548,   550,   552,   554
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,    53,    -1,    53,    54,    -1,    54,    -1,
      56,    -1,    64,    -1,    55,    -1,     1,    -1,    11,     5,
      45,    73,    46,    -1,    62,    58,    49,    -1,     1,    58,
      49,    -1,    62,     1,    49,    -1,    61,    58,    49,    -1,
       1,    58,    49,    -1,    61,     1,    49,    -1,    58,    47,
      59,    -1,    58,    47,     1,    -1,    59,    -1,     1,    -1,
      60,    -1,    60,    48,    83,    -1,     1,    48,    83,    -1,
      60,    48,     1,    -1,     5,    -1,     5,    43,     3,    44,
      -1,     5,    43,     1,    -1,     1,    44,    -1,    12,    62,
      -1,    62,    -1,    63,    -1,     6,    -1,    13,    -1,    14,
      -1,    15,    -1,    62,     5,    41,    65,    42,    70,    -1,
      62,     1,    -1,    62,     5,    41,     1,    -1,    62,     5,
      41,    65,    41,     1,    -1,     5,    41,    65,    42,    70,
      -1,     5,    41,     1,    -1,     5,    41,    65,    42,     1,
      -1,    66,    -1,    -1,    66,    49,    67,    -1,    66,    49,
       1,    -1,    67,    -1,     1,    -1,    62,    68,    -1,    62,
       1,    -1,    68,    47,    69,    -1,    68,    47,     1,    -1,
      69,    -1,     1,    -1,     5,    -1,     5,    43,    44,    -1,
       1,    44,    -1,    76,    -1,    71,    -1,    75,    -1,    72,
      -1,    80,    -1,    81,    -1,    45,    73,    74,    46,    -1,
      45,     1,    74,    46,    -1,    45,    73,     1,    46,    -1,
      73,    57,    -1,    -1,    74,    70,    -1,    -1,    82,    49,
      -1,    49,    -1,    77,    -1,    79,    -1,    16,    41,    83,
      42,    78,    17,    78,    -1,    16,     1,    42,    78,    17,
      78,    -1,    18,    41,    83,    42,    78,    -1,    18,     1,
      42,    78,    -1,    18,    41,     1,    42,    78,    -1,    16,
      41,    83,    42,    78,    17,    78,    -1,    16,    41,     1,
      -1,    16,     1,    42,    78,    17,    78,    -1,    18,    41,
      83,    42,    78,    -1,    18,     1,    42,    78,    -1,    18,
      41,     1,    42,    78,    -1,    18,     1,    -1,    71,    -1,
       1,    -1,    16,    41,    83,    42,    78,    -1,    16,    41,
      83,    42,    79,    -1,    16,    41,    83,    42,    78,    17,
      79,    -1,    16,     1,    -1,    16,     1,    42,    79,    -1,
      16,     1,    42,    78,    17,    79,    -1,    18,    41,    83,
      42,    79,    -1,    18,     1,    42,    79,    -1,    18,    41,
       1,    42,    79,    -1,    19,    49,    -1,    19,    82,    49,
      -1,    20,    49,    -1,    95,    35,    82,    -1,     1,    35,
       1,    -1,    95,    23,    82,    -1,    95,    24,    82,    -1,
      95,    25,    82,    -1,    95,    26,    82,    -1,    95,    28,
      -1,     1,    28,    -1,    95,    27,    -1,     1,    27,    -1,
      83,    -1,    83,    10,    84,    -1,    83,    10,     1,    -1,
      84,    -1,    84,     9,    85,    -1,    84,     9,     1,    -1,
      85,    -1,     8,    85,    -1,     8,     1,    -1,    86,    -1,
      88,    87,    88,    -1,    88,    87,     1,    -1,     1,    87,
      88,    -1,    88,    -1,    31,    -1,    32,    -1,    34,    -1,
      33,    -1,    29,    -1,    30,    -1,    88,    89,    90,    -1,
      88,    89,     1,    -1,    90,    -1,    37,    -1,    38,    -1,
      90,    91,    92,    -1,    90,    91,     1,    -1,    92,    -1,
      36,    -1,    39,    -1,    40,    -1,    93,    92,    -1,    93,
       1,    -1,    94,    -1,    38,    -1,    36,    -1,    21,    -1,
      96,    -1,    95,    -1,     5,    -1,    95,    43,    82,    44,
      -1,    95,    22,     5,    -1,    41,    82,    42,    -1,    41,
       1,    -1,     1,    42,    -1,    97,    -1,   100,    -1,     5,
      41,    98,    42,    -1,     1,    41,    -1,    99,    -1,    -1,
      99,    47,    82,    -1,    99,    47,     1,    -1,    82,    -1,
       3,    -1,     4,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   122,   122,   126,   144,   149,   151,   153,   155,   158,
     173,   191,   192,   196,   215,   217,   221,   241,   243,   247,
     250,   254,   261,   263,   267,   275,   284,   285,   290,   296,
     303,   308,   314,   318,   322,   328,   339,   340,   341,   343,
     353,   354,   358,   363,   368,   388,   390,   394,   398,   415,
     418,   438,   440,   445,   448,   455,   462,   467,   469,   473,
     475,   477,   479,   484,   498,   500,   504,   524,   529,   549,
     554,   560,   570,   572,   577,   589,   593,   603,   605,   609,
     621,   622,   625,   636,   638,   640,   642,   646,   649,   659,
     669,   681,   683,   685,   690,   702,   704,   709,   718,   730,
     741,   751,   753,   763,   772,   781,   790,   800,   803,   813,
     816,   823,   832,   833,   840,   848,   849,   855,   863,   865,
     871,   880,   881,   883,   890,   892,   894,   896,   898,   900,
     904,   914,   916,   922,   924,   928,   938,   940,   944,   946,
     948,   952,   960,   961,   965,   967,   969,   973,   975,   979,
     984,   992,  1007,  1013,  1014,  1017,  1021,  1027,  1037,  1041,
    1046,  1052,  1070,  1071,  1077,  1083,  1089
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMCONST", "CHARCONST", "ID", "RECTYPE",
  "BOOLCONST", "NOT", "AND", "OR", "RECORD", "STATIC", "INT", "BOOL",
  "CHAR", "IF", "ELSE", "WHILE", "RETURN", "BREAK", "RAND", "DOT",
  "ADDASS", "SUBASS", "MULASS", "DIVASS", "DEC", "INC", "EQ", "NOTEQ",
  "LESSEQ", "LT", "GRTEQ", "GT", "ASS", "MUL", "ADD", "SUB", "DIV", "MOD",
  "LPAREN", "RPAREN", "LBRAC", "RBRAC", "LCUR", "RCUR", "COMMA", "COL",
  "SEMI", "ERR", "$accept", "program", "declarationList", "declaration",
  "recDeclaration", "varDeclaration", "scopedVarDeclaration",
  "varDeclList", "varDeclInitialize", "varDeclId", "scopedTypeSpecifier",
  "typeSpecifier", "returnTypeSpecifier", "funDeclaration", "params",
  "paramList", "paramTypeList", "paramIdList", "paramId", "statement",
  "otherStatement", "compoundStmt", "localDeclarations", "statementList",
  "expressionStmt", "selectIterStmt", "firstmatched", "matched",
  "unmatched", "returnStmt", "breakStmt", "expression", "simpleExpression",
  "andExpression", "unaryRelExpression", "relExpression", "relop",
  "sumExpression", "sumop", "term", "mulop", "unaryExpression", "unaryop",
  "factor", "mutable", "immutable", "call", "args", "argList", "constant", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    54,    54,    55,
      56,    56,    56,    57,    57,    57,    58,    58,    58,    58,
      59,    59,    59,    59,    60,    60,    60,    60,    61,    61,
      62,    62,    63,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    65,    65,    66,    66,    66,    66,    67,    67,
      68,    68,    68,    68,    69,    69,    69,    70,    70,    71,
      71,    71,    71,    72,    72,    72,    73,    73,    74,    74,
      75,    75,    76,    76,    77,    77,    77,    77,    77,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    80,    80,    81,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    83,    83,    83,    84,    84,    84,    85,    85,    85,
      86,    86,    86,    86,    87,    87,    87,    87,    87,    87,
      88,    88,    88,    89,    89,    90,    90,    90,    91,    91,
      91,    92,    92,    92,    93,    93,    93,    94,    94,    95,
      95,    95,    96,    96,    96,    96,    96,    97,    97,    98,
      98,    99,    99,    99,   100,   100,   100
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     3,     3,     3,     1,     4,     3,     2,     2,     1,
       1,     1,     1,     1,     1,     6,     2,     4,     6,     5,
       3,     5,     1,     0,     3,     3,     1,     1,     2,     2,
       3,     3,     1,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     4,     4,     4,     2,     0,     2,     0,
       2,     1,     1,     1,     7,     6,     5,     4,     5,     7,
       3,     6,     5,     4,     5,     2,     1,     1,     5,     5,
       7,     2,     4,     6,     5,     4,     5,     2,     3,     2,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     2,
       1,     3,     3,     1,     3,     3,     1,     2,     2,     1,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     1,     1,     3,     3,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       4,     3,     3,     2,     2,     1,     1,     4,     2,     1,
       0,     3,     3,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    31,     0,    32,    33,    34,     0,     0,
       4,     7,     5,     0,    30,     6,    19,    24,     0,    18,
      20,     0,     0,     1,     3,    36,    24,     0,    27,     0,
       0,     0,    11,     0,    40,     0,     0,    42,    46,    67,
      12,     0,    10,     0,   164,   165,   149,   166,     0,   146,
     145,   144,     0,    22,   113,   116,   119,   123,   132,   137,
       0,   143,   148,   147,   155,   156,    26,     0,    17,    16,
      23,    21,    49,    54,    48,    52,     0,     0,     0,    37,
       0,   128,   129,   124,   125,   127,   126,   158,   154,     0,
       0,   118,   117,   153,     0,   110,   148,     0,     0,   133,
     134,     0,     0,   138,   139,   140,     0,   142,   141,     0,
       0,    25,    56,     0,     0,    41,     0,     0,     0,     0,
       0,    71,    39,    58,    60,    59,    57,    72,    73,    61,
      62,     0,    45,    44,     0,     0,     9,    66,     0,    29,
       0,     0,     0,   122,     0,   163,     0,   159,   109,   107,
       0,   152,     0,     0,     0,     0,   108,   106,     0,   112,
     111,   115,   114,   121,   120,   131,   130,   136,   135,   151,
       0,    55,    51,    50,    91,     0,     0,     0,    97,     0,
      99,    69,     0,    70,     0,    28,    19,     0,    38,    35,
     157,     0,   101,   102,   103,   104,   105,   100,   150,     0,
       0,     0,     0,     0,    98,     0,     0,     0,    14,    15,
      13,   162,   161,    87,     0,     0,    86,     0,    92,     0,
      77,    95,     0,     0,    64,    68,    65,    63,    91,     0,
      85,     0,     0,    88,    89,    78,    96,    76,    94,     0,
      80,     0,     0,     0,     0,    75,    93,     0,     0,     0,
      83,     0,     0,    74,    90,     0,    88,    84,    82,    81,
       0,    79
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    10,    11,    12,   137,   184,    19,    20,
     138,    35,    14,    15,    36,    37,    38,    74,    75,   225,
     216,   124,    78,   205,   125,   126,   127,   217,   128,   129,
     130,   131,    95,    54,    55,    56,    89,    57,   102,    58,
     106,    59,    60,    61,    96,    63,    64,   146,   147,    65
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -199
static const yytype_int16 yypact[] =
{
     115,   754,   -14,  -199,    27,  -199,  -199,  -199,    40,   770,
    -199,  -199,  -199,    80,  -199,  -199,    79,     3,   114,  -199,
      34,   118,    26,  -199,  -199,   127,   171,   180,  -199,   318,
     234,   134,  -199,   365,   -20,   161,    50,    48,  -199,  -199,
    -199,   219,  -199,   757,  -199,  -199,    67,  -199,   490,  -199,
    -199,  -199,   512,   101,   113,  -199,  -199,   783,   105,  -199,
     648,  -199,    -5,  -199,  -199,  -199,  -199,    81,    79,  -199,
     757,   101,    43,    93,    95,  -199,   391,    22,    88,    68,
     204,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,   656,
     418,   757,  -199,   716,   122,   101,   699,   531,   539,  -199,
    -199,   667,   675,  -199,  -199,  -199,   697,   239,  -199,   150,
     558,  -199,  -199,   128,   172,   716,     6,     7,   271,   144,
     203,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,
    -199,   156,  -199,  -199,   194,    92,  -199,  -199,   225,  -199,
     212,   430,   239,   245,   716,  -199,   186,   184,  -199,  -199,
     242,  -199,   558,   558,   558,   558,  -199,  -199,   558,   757,
     113,   757,  -199,   239,   245,   239,   105,   239,  -199,  -199,
     206,  -199,   215,  -199,   205,   318,   231,   580,  -199,   218,
    -199,  -199,   250,  -199,   189,  -199,   148,   193,  -199,  -199,
    -199,   599,  -199,  -199,  -199,  -199,  -199,  -199,  -199,   469,
      16,   469,   763,    23,  -199,   297,    15,   344,  -199,  -199,
    -199,   716,  -199,   716,    14,    38,  -199,   260,  -199,   469,
    -199,  -199,   149,   469,  -199,  -199,  -199,  -199,   243,   607,
     247,   626,   469,   267,  -199,  -199,  -199,  -199,  -199,   469,
     757,    42,   469,   777,    46,  -199,  -199,   469,   270,   469,
    -199,   149,   469,  -199,  -199,   469,   273,  -199,  -199,  -199,
     469,  -199
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -199,  -199,  -199,   284,  -199,  -199,  -199,     5,   263,  -199,
    -199,     2,  -199,  -199,   256,  -199,   226,  -199,   192,   -66,
     -67,  -199,   188,   129,  -199,  -199,  -199,  -198,  -156,  -199,
    -199,   -40,   -28,   213,   -34,  -199,   257,   -59,  -199,   222,
    -199,   -47,  -199,  -199,   -29,  -199,  -199,  -199,  -199,  -199
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -161
static const yytype_int16 yytable[] =
{
      62,    53,    13,   220,    62,    71,    18,   174,   176,   123,
     122,    13,    94,   108,    92,   228,    16,   109,    27,    62,
      17,   233,   -47,   132,   235,   237,    97,    21,     3,   -47,
     143,    62,    22,    97,   245,     5,     6,     7,   110,   230,
      23,   248,   164,   218,   250,   221,    30,   175,   177,   253,
     145,   256,    97,   257,   258,   229,    97,   259,   219,   168,
      62,   226,   261,   234,   162,   223,   236,   238,    62,    62,
     170,    39,    62,    62,   123,   189,   246,    62,   179,   231,
     139,    25,    33,   218,   249,    26,   221,   112,   252,   134,
     -53,   254,    76,   234,     3,   236,   238,    77,     3,   246,
     135,     5,     6,     7,   254,     5,     6,     7,    90,   -47,
     -47,    97,   193,   194,   195,   196,     1,   -47,   197,    34,
       2,     3,    98,    28,     3,   111,     4,    29,     5,     6,
       7,     5,     6,     7,   136,    68,   113,   185,   123,    17,
     123,   103,   114,   187,   104,   105,    62,   200,    62,   203,
     213,   212,    44,    45,    46,   169,    47,    48,  -154,  -154,
     -43,    31,    72,    32,   151,   214,    73,   215,   118,   119,
      49,    28,   171,   172,   -19,    29,    40,    73,  -154,  -154,
    -154,  -154,  -154,  -154,   139,    50,  -154,    51,  -154,  -154,
      52,  -154,    28,   180,   120,    16,    29,   209,   121,    17,
      62,   241,    62,   244,   181,   183,   -67,   -67,   -67,   -67,
     -67,   -67,    41,   188,    30,   -67,   -67,   -67,   -67,   -67,
      79,   -67,   -67,   -67,   -67,     3,   186,    31,   190,    42,
      17,   191,     5,     6,     7,    66,    31,    67,   208,   -67,
      31,   -67,   210,   192,   -67,   140,   141,   199,   -67,   -67,
     198,   206,   -67,   -69,   -69,   -69,     3,   -69,   -69,   112,
     -43,   -43,   135,     5,     6,     7,   -69,   204,   -69,   -69,
     -69,   -69,   144,   201,    44,    45,    46,   232,    47,    48,
      87,    88,    99,   100,   247,   239,   -69,   255,   -69,   242,
     260,   -69,    49,    24,    69,   -69,   -69,    80,   144,   -69,
      44,    45,    46,   133,    47,    48,   173,    50,   182,    51,
     160,   207,    52,   116,   101,   117,   118,   119,    49,    43,
     178,    44,    45,    46,   166,    47,    48,     0,     0,     0,
       0,     0,     0,    50,     0,    51,     0,     0,    52,    49,
       0,     0,   120,   224,     0,   144,   121,    44,    45,    46,
       0,    47,    48,     0,    50,     0,    51,     0,     0,    52,
     116,     0,   117,   118,   119,    49,    70,     0,    44,    45,
      46,     0,    47,    48,     0,     0,     0,     0,     0,     0,
      50,     0,    51,     0,     0,    52,    49,     0,     0,   120,
     227,     0,   115,   121,    44,    45,    46,     0,    47,    48,
       0,    50,     0,    51,     0,     0,    52,   116,     0,   117,
     118,   119,    49,     0,     0,     0,     0,     0,     0,   144,
       0,    44,    45,    46,     0,    47,    48,    50,     0,    51,
       0,   144,    52,    44,    45,    46,   120,    47,    48,    49,
     121,     0,     0,     0,     0,     0,   116,     0,   117,   118,
     119,    49,     0,     0,    50,     0,    51,     0,     0,    52,
    -160,     0,     0,     0,     0,     0,    50,     0,    51,     0,
     213,    52,    44,    45,    46,   120,    47,    48,     0,   121,
       0,     0,     0,     0,     0,   214,     0,   215,   118,   119,
      49,    91,     0,    44,    45,    46,     0,    47,    48,     0,
       0,     0,     0,     0,     0,    50,     0,    51,     0,     0,
      52,    49,     0,    93,   120,    44,    45,    46,   121,    47,
      48,     0,     0,     0,     0,     0,    50,     0,    51,     0,
       0,    52,   159,    49,    44,    45,    46,     0,    47,    48,
     161,     0,    44,    45,    46,     0,    47,    48,    50,     0,
      51,     0,    49,    52,     0,     0,     0,     0,     0,   144,
      49,    44,    45,    46,     0,    47,    48,    50,     0,    51,
       0,     0,    52,     0,     0,    50,     0,    51,     0,    49,
      52,   202,     0,    44,    45,    46,     0,    47,    48,     0,
       0,     0,     0,     0,    50,     0,    51,     0,     0,    52,
     211,    49,    44,    45,    46,     0,    47,    48,   240,     0,
      44,    45,    46,     0,    47,    48,    50,     0,    51,     0,
      49,    52,     0,     0,     0,     0,     0,   243,    49,    44,
      45,    46,     0,    47,    48,    50,     0,    51,     0,     0,
      52,     0,     0,    50,     0,    51,     0,    49,    52,   107,
       0,    44,    45,    46,     0,    47,     0,   142,     0,    44,
      45,    46,    50,    47,    51,     0,     0,    52,   163,    49,
      44,    45,    46,     0,    47,     0,   165,    49,    44,    45,
      46,     0,    47,     0,    50,     0,    51,     0,    49,    52,
       0,     0,    50,     0,    51,     0,    49,    52,   167,     0,
      44,    45,    46,    50,    47,    51,     0,     0,    52,     0,
       0,    50,     0,    51,     0,     0,    52,     0,    49,     0,
       0,   109,   152,   153,   154,   155,   156,   157,     0,     0,
       0,     0,     0,    50,   158,    51,     0,     0,    52,     0,
       0,     0,   110,   148,   149,    81,    82,    83,    84,    85,
      86,   150,     0,     0,    -8,    16,     0,    87,    88,    17,
      -8,     0,     0,     0,     0,    -8,     0,    -8,    -8,    -8,
      -2,     1,     0,     0,     0,     2,     3,     0,     0,     0,
       0,     4,     0,     5,     6,     7,    81,    82,    83,    84,
      85,    86,    81,    82,    83,    84,    85,    86,    87,    88,
       0,     0,     0,     0,    87,   222,    81,    82,    83,    84,
      85,    86,    81,    82,    83,    84,    85,    86,    87,   251,
      99,   100
};

static const yytype_int16 yycheck[] =
{
      29,    29,     0,   201,    33,    33,     1,     1,     1,    76,
      76,     9,    52,    60,    48,     1,     1,    22,    13,    48,
       5,   219,    42,     1,   222,   223,    10,    41,     6,    49,
      89,    60,     5,    10,   232,    13,    14,    15,    43,     1,
       0,   239,   101,   199,   242,   201,    43,    41,    41,   247,
      90,   249,    10,   251,   252,    41,    10,   255,    42,   106,
      89,    46,   260,   219,    98,    42,   222,   223,    97,    98,
     110,    45,   101,   102,   141,   141,   232,   106,   118,    41,
      78,     1,    48,   239,    42,     5,   242,    44,    42,     1,
      47,   247,    42,   249,     6,   251,   252,    49,     6,   255,
      12,    13,    14,    15,   260,    13,    14,    15,    41,    41,
      42,    10,   152,   153,   154,   155,     1,    49,   158,     1,
       5,     6,     9,    44,     6,    44,    11,    48,    13,    14,
      15,    13,    14,    15,    46,     1,    43,   135,   205,     5,
     207,    36,    47,   138,    39,    40,   175,   175,   177,   177,
       1,   191,     3,     4,     5,     5,     7,     8,     9,    10,
      42,    47,     1,    49,    42,    16,     5,    18,    19,    20,
      21,    44,    44,     1,    47,    48,    49,     5,    29,    30,
      31,    32,    33,    34,   182,    36,    37,    38,    39,    40,
      41,    42,    44,    49,    45,     1,    48,    49,    49,     5,
     229,   229,   231,   231,     1,    49,     3,     4,     5,     6,
       7,     8,    41,     1,    43,    12,    13,    14,    15,    16,
       1,    18,    19,    20,    21,     6,     1,    47,    42,    49,
       5,    47,    13,    14,    15,     1,    47,     3,    49,    36,
      47,    38,    49,     1,    41,    41,    42,    42,    45,    46,
      44,     1,    49,     3,     4,     5,     6,     7,     8,    44,
      41,    42,    12,    13,    14,    15,    16,    49,    18,    19,
      20,    21,     1,    42,     3,     4,     5,    17,     7,     8,
      41,    42,    37,    38,    17,    42,    36,    17,    38,    42,
      17,    41,    21,     9,    31,    45,    46,    41,     1,    49,
       3,     4,     5,    77,     7,     8,   114,    36,   120,    38,
      97,   182,    41,    16,    57,    18,    19,    20,    21,     1,
      49,     3,     4,     5,   102,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    38,    -1,    -1,    41,    21,
      -1,    -1,    45,    46,    -1,     1,    49,     3,     4,     5,
      -1,     7,     8,    -1,    36,    -1,    38,    -1,    -1,    41,
      16,    -1,    18,    19,    20,    21,     1,    -1,     3,     4,
       5,    -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    38,    -1,    -1,    41,    21,    -1,    -1,    45,
      46,    -1,     1,    49,     3,     4,     5,    -1,     7,     8,
      -1,    36,    -1,    38,    -1,    -1,    41,    16,    -1,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,     3,     4,     5,    -1,     7,     8,    36,    -1,    38,
      -1,     1,    41,     3,     4,     5,    45,     7,     8,    21,
      49,    -1,    -1,    -1,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    -1,    -1,    36,    -1,    38,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    -1,    36,    -1,    38,    -1,
       1,    41,     3,     4,     5,    45,     7,     8,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    16,    -1,    18,    19,    20,
      21,     1,    -1,     3,     4,     5,    -1,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    38,    -1,    -1,
      41,    21,    -1,     1,    45,     3,     4,     5,    49,     7,
       8,    -1,    -1,    -1,    -1,    -1,    36,    -1,    38,    -1,
      -1,    41,     1,    21,     3,     4,     5,    -1,     7,     8,
       1,    -1,     3,     4,     5,    -1,     7,     8,    36,    -1,
      38,    -1,    21,    41,    -1,    -1,    -1,    -1,    -1,     1,
      21,     3,     4,     5,    -1,     7,     8,    36,    -1,    38,
      -1,    -1,    41,    -1,    -1,    36,    -1,    38,    -1,    21,
      41,     1,    -1,     3,     4,     5,    -1,     7,     8,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    38,    -1,    -1,    41,
       1,    21,     3,     4,     5,    -1,     7,     8,     1,    -1,
       3,     4,     5,    -1,     7,     8,    36,    -1,    38,    -1,
      21,    41,    -1,    -1,    -1,    -1,    -1,     1,    21,     3,
       4,     5,    -1,     7,     8,    36,    -1,    38,    -1,    -1,
      41,    -1,    -1,    36,    -1,    38,    -1,    21,    41,     1,
      -1,     3,     4,     5,    -1,     7,    -1,     1,    -1,     3,
       4,     5,    36,     7,    38,    -1,    -1,    41,     1,    21,
       3,     4,     5,    -1,     7,    -1,     1,    21,     3,     4,
       5,    -1,     7,    -1,    36,    -1,    38,    -1,    21,    41,
      -1,    -1,    36,    -1,    38,    -1,    21,    41,     1,    -1,
       3,     4,     5,    36,     7,    38,    -1,    -1,    41,    -1,
      -1,    36,    -1,    38,    -1,    -1,    41,    -1,    21,    -1,
      -1,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      -1,    -1,    -1,    36,    35,    38,    -1,    -1,    41,    -1,
      -1,    -1,    43,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    -1,     0,     1,    -1,    41,    42,     5,
       6,    -1,    -1,    -1,    -1,    11,    -1,    13,    14,    15,
       0,     1,    -1,    -1,    -1,     5,     6,    -1,    -1,    -1,
      -1,    11,    -1,    13,    14,    15,    29,    30,    31,    32,
      33,    34,    29,    30,    31,    32,    33,    34,    41,    42,
      -1,    -1,    -1,    -1,    41,    42,    29,    30,    31,    32,
      33,    34,    29,    30,    31,    32,    33,    34,    41,    42,
      37,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     5,     6,    11,    13,    14,    15,    52,    53,
      54,    55,    56,    62,    63,    64,     1,     5,    58,    59,
      60,    41,     5,     0,    54,     1,     5,    58,    44,    48,
      43,    47,    49,    48,     1,    62,    65,    66,    67,    45,
      49,    41,    49,     1,     3,     4,     5,     7,     8,    21,
      36,    38,    41,    83,    84,    85,    86,    88,    90,    92,
      93,    94,    95,    96,    97,   100,     1,     3,     1,    59,
       1,    83,     1,     5,    68,    69,    42,    49,    73,     1,
      65,    29,    30,    31,    32,    33,    34,    41,    42,    87,
      41,     1,    85,     1,    82,    83,    95,    10,     9,    37,
      38,    87,    89,    36,    39,    40,    91,     1,    92,    22,
      43,    44,    44,    43,    47,     1,    16,    18,    19,    20,
      45,    49,    70,    71,    72,    75,    76,    77,    79,    80,
      81,    82,     1,    67,     1,    12,    46,    57,    61,    62,
      41,    42,     1,    88,     1,    82,    98,    99,    27,    28,
      35,    42,    23,    24,    25,    26,    27,    28,    35,     1,
      84,     1,    85,     1,    88,     1,    90,     1,    92,     5,
      82,    44,     1,    69,     1,    41,     1,    41,    49,    82,
      49,     1,    73,    49,    58,    62,     1,    58,     1,    70,
      42,    47,     1,    82,    82,    82,    82,    82,    44,    42,
      83,    42,     1,    83,    49,    74,     1,    74,    49,    49,
      49,     1,    82,     1,    16,    18,    71,    78,    79,    42,
      78,    79,    42,    42,    46,    70,    46,    46,     1,    41,
       1,    41,    17,    78,    79,    78,    79,    78,    79,    42,
       1,    83,    42,     1,    83,    78,    79,    17,    78,    42,
      78,    42,    42,    78,    79,    17,    78,    78,    78,    78,
      17,    78
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 123 "parser.y"
    {savedTree = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 3:
#line 127 "parser.y"
    {
								TreeNode * t = (yyvsp[(1) - (2)].treeNode);
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = (yyvsp[(2) - (2)].treeNode);
									(yyval.treeNode) = (yyvsp[(1) - (2)].treeNode);
								}
								else 
								{
									(yyval.treeNode) = (yyvsp[(2) - (2)].treeNode);
								}
							;}
    break;

  case 4:
#line 145 "parser.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 5:
#line 150 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 6:
#line 152 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 7:
#line 154 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 9:
#line 159 "parser.y"
    {

								(yyval.treeNode) = newDeclNode(recDeclaration);
								(yyval.treeNode) -> isRecord = true;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (5)].tokenData) -> lineno;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (5)].tokenData) -> tokenString);
								st.insert((yyval.treeNode) -> attr.name, (char *)"RECORD");
								//st.print(pointerPrintStr); 
								(yyval.treeNode) -> child[0] = (yyvsp[(4) - (5)].treeNode);
								(yyval.treeNode) -> numChildren = 1;
								
							;}
    break;

  case 10:
#line 174 "parser.y"
    {
								TreeNode * t = (yyvsp[(2) - (3)].treeNode);
								if (t != NULL)
								{
									do 
									{
										t -> type = (yyvsp[(1) - (3)].expType);
										t = t -> sibling;
									} while (t != NULL);
									(yyval.treeNode) = (yyvsp[(2) - (3)].treeNode);
								}
								else 
								{
									(yyval.treeNode) = NULL;
								}
								yyerrok;
 							;}
    break;

  case 12:
#line 193 "parser.y"
    {yyerrok;;}
    break;

  case 13:
#line 197 "parser.y"
    {
								TreeNode * t = (yyvsp[(2) - (3)].treeNode);
								if (t != NULL)
								{
									do 
									{
										t -> type = (yyvsp[(1) - (3)].treeNode) -> type;
										t -> isStatic = (yyvsp[(1) - (3)].treeNode) -> isStatic;
										t = t -> sibling;
									} while (t != NULL);
									(yyval.treeNode) = (yyvsp[(2) - (3)].treeNode);
								}
								else 
								{
									(yyval.treeNode) = NULL;
								}
								yyerrok;
							;}
    break;

  case 14:
#line 216 "parser.y"
    {yyerrok;;}
    break;

  case 15:
#line 218 "parser.y"
    {yyerrok;;}
    break;

  case 16:
#line 222 "parser.y"
    {
								TreeNode * t = (yyvsp[(1) - (3)].treeNode);
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = (yyvsp[(3) - (3)].treeNode);
									(yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);
									
								}
								else 
								{
									(yyval.treeNode) = (yyvsp[(3) - (3)].treeNode);
									
								}
								yyerrok;
							;}
    break;

  case 18:
#line 244 "parser.y"
    { 
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); 
							;}
    break;

  case 20:
#line 251 "parser.y"
    {	
 								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 21:
#line 255 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[0] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 1;
								
							;}
    break;

  case 22:
#line 262 "parser.y"
    {yyerrok;;}
    break;

  case 24:
#line 268 "parser.y"
    {
								(yyval.treeNode) = newDeclNode(varDeclaration);
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(1) - (1)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (1)].tokenData) -> lineno;
								(yyval.treeNode)->isArray = false;
								//$$ -> isStatic = isStatic;
							;}
    break;

  case 25:
#line 276 "parser.y"
    {

								(yyval.treeNode) = newDeclNode(varDeclaration);
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(1) - (4)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (4)].tokenData) -> lineno;
								(yyval.treeNode)->isArray = true; 
								//$$ -> isStatic = isStatic;
							;}
    break;

  case 27:
#line 286 "parser.y"
    {yyerrok;;}
    break;

  case 28:
#line 291 "parser.y"
    {
								(yyval.treeNode) = newDeclNode(varDeclaration);
								(yyval.treeNode) -> isStatic = true;
								(yyval.treeNode) -> type = (yyvsp[(2) - (2)].expType);
							;}
    break;

  case 29:
#line 297 "parser.y"
    { 
								(yyval.treeNode) = newDeclNode(varDeclaration);
								(yyval.treeNode) -> type = (yyvsp[(1) - (1)].expType);
							;}
    break;

  case 30:
#line 304 "parser.y"
    {
								(yyval.expType) = (yyvsp[(1) - (1)].expType);
							;}
    break;

  case 31:
#line 309 "parser.y"
    {
								(yyval.expType)  = record; 
							;}
    break;

  case 32:
#line 315 "parser.y"
    {
								(yyval.expType) = integer;	
							;}
    break;

  case 33:
#line 319 "parser.y"
    {
								(yyval.expType) = boolean; 
							;}
    break;

  case 34:
#line 323 "parser.y"
    {
								(yyval.expType) = character;
							;}
    break;

  case 35:
#line 329 "parser.y"
    {
								(yyval.treeNode) = newDeclNode(funDeclaration);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (6)].tokenData) -> lineno;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (6)].tokenData) -> tokenString);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> type = (yyvsp[(1) - (6)].expType);
								(yyval.treeNode) -> child[0] = (yyvsp[(4) - (6)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(6) - (6)].treeNode);
								
							;}
    break;

  case 39:
#line 344 "parser.y"
    {
								(yyval.treeNode) = newDeclNode(funDeclaration);
								(yyval.treeNode) -> type = Void;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (5)].tokenData) -> lineno;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(1) - (5)].tokenData) -> tokenString);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> child[0] = (yyvsp[(3) - (5)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(5) - (5)].treeNode); 
							;}
    break;

  case 42:
#line 359 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 43:
#line 363 "parser.y"
    {
								(yyval.treeNode) = NULL;
							;}
    break;

  case 44:
#line 369 "parser.y"
    {
								TreeNode * t = (yyvsp[(1) - (3)].treeNode);
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = (yyvsp[(3) - (3)].treeNode);
									(yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);
									
								}
								else 
								{
									(yyval.treeNode) = (yyvsp[(3) - (3)].treeNode);
									
								}
								yyerrok;
							;}
    break;

  case 46:
#line 391 "parser.y"
    { 
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); 
							;}
    break;

  case 48:
#line 399 "parser.y"
    {
								TreeNode * t = (yyvsp[(2) - (2)].treeNode);
								if (t != NULL)
								{
									do 
									{
										t -> type = (yyvsp[(1) - (2)].expType);
										t = t -> sibling;
									} while (t != NULL);
									(yyval.treeNode) = (yyvsp[(2) - (2)].treeNode);
								}
								else 
								{
									(yyval.treeNode) = NULL;
								}
							;}
    break;

  case 50:
#line 419 "parser.y"
    {
								TreeNode * t = (yyvsp[(1) - (3)].treeNode);
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = (yyvsp[(3) - (3)].treeNode);
									(yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);
								}
								else 
								{
									(yyval.treeNode) = (yyvsp[(3) - (3)].treeNode); 
									
								}
								yyerrok;
							;}
    break;

  case 52:
#line 441 "parser.y"
    { 
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); 
							;}
    break;

  case 54:
#line 449 "parser.y"
    {
								(yyval.treeNode) = newDeclNode(paramDeclaration); 
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(1) - (1)].tokenData) -> tokenString);
								(yyval.treeNode)->isArray = false;
								(yyval.treeNode)->isParam = true;
							;}
    break;

  case 55:
#line 456 "parser.y"
    {
								(yyval.treeNode) = newDeclNode(paramDeclaration);
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(1) - (3)].tokenData) -> tokenString);
								(yyval.treeNode)->isArray = true;
								(yyval.treeNode)->isParam = true;
							;}
    break;

  case 56:
#line 463 "parser.y"
    {yyerrok;;}
    break;

  case 57:
#line 468 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 58:
#line 470 "parser.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 59:
#line 474 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 60:
#line 476 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 61:
#line 478 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 62:
#line 480 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 63:
#line 485 "parser.y"
    {
								(yyval.treeNode) = newStmtNode(compoundStmt); 
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (4)].tokenData) -> lineno;
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> child[0] = (yyvsp[(2) - (4)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (4)].treeNode); 

								//TODO: Remove this, enter new scope for compoundStmt
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (4)].tokenData) -> tokenString; 
								(yyval.treeNode) -> type = Void;

								yyerrok;
							;}
    break;

  case 64:
#line 499 "parser.y"
    {yyerrok;;}
    break;

  case 65:
#line 501 "parser.y"
    {yyerrok;;}
    break;

  case 66:
#line 505 "parser.y"
    {
								TreeNode * t = (yyvsp[(1) - (2)].treeNode);
								if (t != NULL)
								{
									while (t -> sibling != NULL)
									{
										t = t -> sibling;
									}
									t -> sibling = (yyvsp[(2) - (2)].treeNode);
									(yyval.treeNode) = (yyvsp[(1) - (2)].treeNode);
								}
								else
								{
									(yyval.treeNode) = (yyvsp[(2) - (2)].treeNode);
								}
								
							;}
    break;

  case 67:
#line 524 "parser.y"
    {
								(yyval.treeNode) = NULL;
							;}
    break;

  case 68:
#line 530 "parser.y"
    {
								TreeNode * t = (yyvsp[(1) - (2)].treeNode);
								if (t != NULL)
								{
									while (t -> sibling != NULL)
									{
										t = t -> sibling;
									}
									t -> sibling = (yyvsp[(2) - (2)].treeNode);
									(yyval.treeNode) = (yyvsp[(1) - (2)].treeNode);
								}
								else
								{
									(yyval.treeNode) = (yyvsp[(2) - (2)].treeNode);
								}
								
							;}
    break;

  case 69:
#line 549 "parser.y"
    {
								(yyval.treeNode) = NULL;
							;}
    break;

  case 70:
#line 555 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (2)].treeNode);
								yyerrok;
							;}
    break;

  case 71:
#line 561 "parser.y"
    {
								(yyval.treeNode) = NULL;
								//printf("Got here\n");
								yyerrok;
							;}
    break;

  case 72:
#line 571 "parser.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 73:
#line 573 "parser.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 74:
#line 578 "parser.y"
    {
								(yyval.treeNode) = newStmtNode(selectionStmt);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (7)].tokenData) -> tokenString;
								(yyval.treeNode) -> numChildren = 3;
								(yyval.treeNode) -> child[0] = (yyvsp[(3) - (7)].treeNode); 
								(yyval.treeNode) -> child[1] = (yyvsp[(5) - (7)].treeNode);
								(yyval.treeNode) -> child[2] = (yyvsp[(7) - (7)].treeNode);
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (7)].tokenData) -> lineno;
								(yyval.treeNode) -> type = Void;
							;}
    break;

  case 75:
#line 590 "parser.y"
    {yyerrok;;}
    break;

  case 76:
#line 594 "parser.y"
    {
								(yyval.treeNode) = newStmtNode(iterationStmt);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (5)].tokenData) -> tokenString;
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> child[0] = (yyvsp[(3) - (5)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(5) - (5)].treeNode);
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (5)].tokenData) -> lineno;
								(yyval.treeNode) -> type = Void;
							;}
    break;

  case 77:
#line 604 "parser.y"
    {yyerrok;;}
    break;

  case 78:
#line 606 "parser.y"
    {yyerrok;;}
    break;

  case 79:
#line 610 "parser.y"
    {
								(yyval.treeNode) = newStmtNode(selectionStmt);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (7)].tokenData) -> tokenString;
								(yyval.treeNode) -> child[0] = (yyvsp[(3) - (7)].treeNode); 
								(yyval.treeNode) -> child[1] = (yyvsp[(5) - (7)].treeNode);
								(yyval.treeNode) -> child[2] = (yyvsp[(7) - (7)].treeNode);
								(yyval.treeNode) -> numChildren = 3;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (7)].tokenData) -> lineno;
								(yyval.treeNode) -> type = Void;
							;}
    break;

  case 81:
#line 623 "parser.y"
    {yyerrok;;}
    break;

  case 82:
#line 626 "parser.y"
    {
								(yyval.treeNode) = newStmtNode(iterationStmt);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (5)].tokenData) -> tokenString;
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> child[0] = (yyvsp[(3) - (5)].treeNode); 
								(yyval.treeNode) -> child[1] = (yyvsp[(5) - (5)].treeNode);
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (5)].tokenData) -> lineno;
								(yyval.treeNode) -> type = Void;
							;}
    break;

  case 83:
#line 637 "parser.y"
    {yyerrok;;}
    break;

  case 84:
#line 639 "parser.y"
    {yyerrok;;}
    break;

  case 86:
#line 643 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 88:
#line 650 "parser.y"
    {
								(yyval.treeNode) = newStmtNode(selectionStmt);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (5)].tokenData) -> tokenString;
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> child[0] = (yyvsp[(3) - (5)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(5) - (5)].treeNode);
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (5)].tokenData) -> lineno;
								(yyval.treeNode) -> type = Void;
							;}
    break;

  case 89:
#line 660 "parser.y"
    {
								(yyval.treeNode) = newStmtNode(selectionStmt);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (5)].tokenData) -> tokenString;
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> child[0] = (yyvsp[(3) - (5)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(5) - (5)].treeNode);
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (5)].tokenData) -> lineno;
								(yyval.treeNode) -> type = Void;
							;}
    break;

  case 90:
#line 670 "parser.y"
    {
								(yyval.treeNode) = newStmtNode(selectionStmt);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (7)].tokenData) -> tokenString;
								(yyval.treeNode) -> child[0] = (yyvsp[(3) - (7)].treeNode);
								(yyval.treeNode) -> child[2] = (yyvsp[(5) - (7)].treeNode);
								(yyval.treeNode) -> child[2] = (yyvsp[(7) - (7)].treeNode);
								(yyval.treeNode) -> numChildren = 3;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (7)].tokenData) -> lineno;
								(yyval.treeNode) -> type = Void;

							;}
    break;

  case 92:
#line 684 "parser.y"
    {yyerrok;;}
    break;

  case 93:
#line 686 "parser.y"
    {yyerrok;;}
    break;

  case 94:
#line 691 "parser.y"
    {
								(yyval.treeNode) = newStmtNode(iterationStmt);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (5)].tokenData) -> tokenString;
								(yyval.treeNode) -> child[0] = (yyvsp[(3) - (5)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(5) - (5)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (5)].tokenData) -> lineno;
								(yyval.treeNode) -> type = Void;
							;}
    break;

  case 95:
#line 703 "parser.y"
    {yyerrok;;}
    break;

  case 96:
#line 705 "parser.y"
    {yyerrok;;}
    break;

  case 97:
#line 710 "parser.y"
    {
								(yyval.treeNode) = newStmtNode(returnStmt); 
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (2)].tokenData) -> tokenString;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (2)].tokenData) -> lineno;
								(yyval.treeNode) -> type = Void;

								yyerrok;
							;}
    break;

  case 98:
#line 719 "parser.y"
    {
								(yyval.treeNode) = newStmtNode(returnStmt);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (3)].tokenData) -> tokenString;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (3)].tokenData) -> lineno;
								(yyval.treeNode) -> child[0] = (yyvsp[(2) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 1;
								(yyval.treeNode) -> type = Void;
								yyerrok;
							;}
    break;

  case 99:
#line 731 "parser.y"
    {
								(yyval.treeNode) = newStmtNode(breakStmt);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (2)].tokenData) -> tokenString;
								(yyval.treeNode) -> type = Void;
								yyerrok;
							;}
    break;

  case 100:
#line 742 "parser.y"
    {
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].tokenData) -> lineno;
							;}
    break;

  case 102:
#line 754 "parser.y"
    {
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].tokenData) -> lineno;
							;}
    break;

  case 103:
#line 764 "parser.y"
    {
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].tokenData) -> lineno;
							;}
    break;

  case 104:
#line 773 "parser.y"
    {
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].tokenData) -> lineno;
							;}
    break;

  case 105:
#line 782 "parser.y"
    {
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].tokenData) -> lineno;
							;}
    break;

  case 106:
#line 791 "parser.y"
    {
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (2)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (2)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (2)].tokenData) -> lineno;
								yyerrok;
							;}
    break;

  case 107:
#line 801 "parser.y"
    {yyerrok;;}
    break;

  case 108:
#line 804 "parser.y"
    {
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (2)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (2)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (2)].tokenData) -> lineno;
								yyerrok;
							;}
    break;

  case 109:
#line 814 "parser.y"
    {yyerrok;;}
    break;

  case 110:
#line 817 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 111:
#line 824 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);

							;}
    break;

  case 113:
#line 834 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 114:
#line 841 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);
						;}
    break;

  case 116:
#line 850 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 117:
#line 856 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(2) - (2)].treeNode);
								(yyval.treeNode) -> numChildren = 1;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(1) - (2)].tokenData) -> tokenString);
							;}
    break;

  case 119:
#line 866 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 120:
#line 872 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].td) -> tokenString);
							;}
    break;

  case 122:
#line 882 "parser.y"
    {yyerrok;;}
    break;

  case 123:
#line 884 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 124:
#line 891 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 125:
#line 893 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 126:
#line 895 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 127:
#line 897 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 128:
#line 899 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 129:
#line 901 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 130:
#line 905 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].td) -> tokenString;
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].td) -> lineno;
							;}
    break;

  case 131:
#line 915 "parser.y"
    {yyerrok;;}
    break;

  case 132:
#line 917 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 133:
#line 923 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 134:
#line 925 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 135:
#line 929 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].td) -> tokenString;
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].td) -> lineno;
							;}
    break;

  case 137:
#line 941 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 138:
#line 945 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 139:
#line 947 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 140:
#line 949 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 141:
#line 953 "parser.y"
    {	
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(2) - (2)].treeNode);
								(yyval.treeNode) -> numChildren = 1;
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (2)].td) -> tokenString;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (2)].td) -> lineno;
							;}
    break;

  case 143:
#line 962 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 144:
#line 966 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 145:
#line 968 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 146:
#line 970 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 147:
#line 974 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 148:
#line 976 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 149:
#line 980 "parser.y"
    {
								(yyval.treeNode) = newExpNode(IdK);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (1)].tokenData) -> tokenString;
							;}
    break;

  case 150:
#line 985 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (4)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (4)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (4)].tokenData) -> tokenString);
							;}
    break;

  case 151:
#line 993 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].tokenData) -> tokenString;
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								
								TreeNode * t;
								t = newExpNode(IdK);
								t -> attr.name = strdup((yyvsp[(3) - (3)].tokenData) -> tokenString);
								t ->isArray = false;
								(yyval.treeNode) -> child[1] = t;
								(yyval.treeNode) -> numChildren = 2;
							;}
    break;

  case 152:
#line 1008 "parser.y"
    {	
								(yyval.treeNode) = (yyvsp[(2) - (3)].treeNode);
								yyerrok;
							;}
    break;

  case 154:
#line 1015 "parser.y"
    {yyerrok;;}
    break;

  case 155:
#line 1018 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 156:
#line 1022 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 157:
#line 1028 "parser.y"
    {
								(yyval.treeNode) = newExpNode(CallK);
								(yyval.treeNode) -> child[0] = (yyvsp[(3) - (4)].treeNode);
								(yyval.treeNode) -> numChildren = 1;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(1) - (4)].tokenData) -> tokenString);
								(yyval.treeNode) ->isArray = false;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (4)].tokenData) -> lineno;

							;}
    break;

  case 158:
#line 1038 "parser.y"
    {yyerrok;;}
    break;

  case 159:
#line 1042 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 160:
#line 1046 "parser.y"
    {
								(yyval.treeNode) = NULL;
							;}
    break;

  case 161:
#line 1053 "parser.y"
    {
								TreeNode *t = (yyvsp[(1) - (3)].treeNode);
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t->sibling;
									}
									t->sibling = (yyvsp[(3) - (3)].treeNode);
									(yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);
								}
								else 
								{
									(yyval.treeNode) = (yyvsp[(3) - (3)].treeNode);
								}
								yyerrok;
							;}
    break;

  case 163:
#line 1072 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 164:
#line 1078 "parser.y"
    {
								(yyval.treeNode) = newExpNode(constK);
								(yyval.treeNode) ->attr.value = (yyvsp[(1) - (1)].tokenData)->numVal;
								(yyval.treeNode) -> type = integer;
							;}
    break;

  case 165:
#line 1084 "parser.y"
    {
								(yyval.treeNode) = newExpNode(constK);
								(yyval.treeNode) ->attr.cvalue = (yyvsp[(1) - (1)].tokenData)->charVal;
								(yyval.treeNode) -> type = character;
							;}
    break;

  case 166:
#line 1090 "parser.y"
    {
								(yyval.treeNode) = newExpNode(constK);
								(yyval.treeNode) -> attr.bvalue = (yyvsp[(1) - (1)].tokenData)->bvalue;
								(yyval.treeNode) -> type = boolean;
							;}
    break;


/* Line 1267 of yacc.c.  */
#line 3062 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1097 "parser.y"


int main(int argc, char *argv[])
{

	extern int yydebug;
	int optCount = 1;
	int printingTree = 0;
	numWarnings = 0;
	numErrors = 0;

	bool capP;


	
	
	// for options
	int opt; 

	while ((opt = getopt(argc, argv, "dpP::")) != -1)
	{
		switch (opt)
		{
			case 'd':
				yydebug = 1;
				break;
			case 'p':
				printingTree = 1;
				capP = false;
				break;
			case 'P':
				printingTree = 1;
				capP = true;
				break;
		}
		optCount++;
	}
	

	if(optCount < argc)
	{
		FILE *infile = fopen(argv[optCount], "r");
		if (infile == NULL)
		{
			printError(-1, 0, argv[optCount], 0, na, na, 0);
			exit(-1);
		}
		yyin = infile;
	}
	initErrorProcessing();
	yyparse();
	fclose(yyin);
	
	savedTree = setup(setupTree, savedTree);

	// print -p before errors
	if (printingTree == 1 && !capP) //1)
	{
		printTree(savedTree, capP);
	}

	scopeAndTypeR(savedTree);
	

	if(symTab.lookup("main") == NULL)
	{
		printError(-2, 0, NULL, 0, na, na, 0);
	}

	/* Symtab printing stuff 
	//symTab.print(pointerPrintStr);
	//finalSymTab = getSymTab();
	//finalSymTab.print(pointerPrintStr);
	*/

	// print -P w types after errors
	if (printingTree == 1 && capP) //1)
	{
		printTree(savedTree, capP);
	}

	printf("Number of warnings: %d\n", numWarnings);
	printf("Number of errors: %d\n", numErrors);
	//symTab.print(pointerPrintStr);

	return 0;
}

