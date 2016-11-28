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
#define YYLAST   785

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  161
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
     218,   221,   223,   231,   235,   242,   248,   253,   259,   262,
     264,   266,   272,   275,   280,   287,   293,   298,   304,   307,
     311,   314,   318,   322,   326,   330,   334,   338,   342,   346,
     350,   354,   357,   360,   363,   366,   368,   372,   376,   378,
     382,   386,   388,   391,   394,   396,   400,   404,   408,   410,
     412,   414,   416,   418,   420,   422,   426,   430,   432,   434,
     436,   440,   444,   446,   448,   450,   452,   455,   458,   460,
     462,   464,   466,   468,   470,   472,   477,   481,   485,   488,
     491,   493,   495,   500,   503,   505,   506,   510,   514,   516,
     518,   520
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
      60,    -1,    60,    48,    81,    -1,     1,    48,    81,    -1,
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
       1,    44,    -1,    76,    -1,    77,    -1,    75,    -1,    72,
      -1,    78,    -1,    79,    -1,    45,    73,    74,    46,    -1,
      45,     1,    74,    46,    -1,    45,    73,     1,    46,    -1,
      73,    57,    -1,    -1,    74,    70,    -1,    -1,    80,    49,
      -1,    49,    -1,    16,    41,    81,    42,    76,    17,    76,
      -1,    16,    41,     1,    -1,    16,     1,    42,    76,    17,
      76,    -1,    18,    41,    81,    42,    76,    -1,    18,     1,
      42,    76,    -1,    18,    41,     1,    42,    76,    -1,    18,
       1,    -1,    71,    -1,     1,    -1,    16,    41,    81,    42,
      70,    -1,    16,     1,    -1,    16,     1,    42,    70,    -1,
      16,     1,    42,    76,    17,    77,    -1,    18,    41,    81,
      42,    70,    -1,    18,     1,    42,    77,    -1,    18,    41,
       1,    42,    77,    -1,    19,    49,    -1,    19,    80,    49,
      -1,    20,    49,    -1,    93,    35,    80,    -1,     1,    35,
       1,    -1,    93,    23,    80,    -1,     1,    23,     1,    -1,
      93,    24,    80,    -1,     1,    24,     1,    -1,    93,    25,
      80,    -1,     1,    25,     1,    -1,    93,    26,    80,    -1,
       1,    26,     1,    -1,    93,    28,    -1,     1,    28,    -1,
      93,    27,    -1,     1,    27,    -1,    81,    -1,    81,    10,
      82,    -1,    81,    10,     1,    -1,    82,    -1,    82,     9,
      83,    -1,    82,     9,     1,    -1,    83,    -1,     8,    83,
      -1,     8,     1,    -1,    84,    -1,    86,    85,    86,    -1,
      86,    85,     1,    -1,     1,    85,    86,    -1,    86,    -1,
      31,    -1,    32,    -1,    34,    -1,    33,    -1,    29,    -1,
      30,    -1,    86,    87,    88,    -1,    86,    87,     1,    -1,
      88,    -1,    37,    -1,    38,    -1,    88,    89,    90,    -1,
      88,    89,     1,    -1,    90,    -1,    36,    -1,    39,    -1,
      40,    -1,    91,    90,    -1,    91,     1,    -1,    92,    -1,
      38,    -1,    36,    -1,    21,    -1,    94,    -1,    93,    -1,
       5,    -1,    93,    43,    80,    44,    -1,    93,    22,     5,
      -1,    41,    80,    42,    -1,    41,     1,    -1,     1,    42,
      -1,    95,    -1,    98,    -1,     5,    41,    96,    42,    -1,
       1,    41,    -1,    97,    -1,    -1,    97,    47,    80,    -1,
      97,    47,     1,    -1,    80,    -1,     3,    -1,     4,    -1,
       7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   122,   122,   126,   144,   149,   151,   153,   155,   159,
     174,   193,   194,   198,   218,   220,   224,   245,   248,   252,
     256,   260,   267,   269,   274,   282,   292,   294,   299,   305,
     312,   317,   323,   327,   331,   337,   348,   350,   352,   355,
     365,   367,   372,   377,   382,   403,   405,   409,   414,   431,
     435,   456,   459,   464,   468,   475,   482,   487,   489,   493,
     495,   497,   499,   503,   518,   520,   524,   544,   549,   569,
     575,   582,   593,   605,   607,   611,   622,   624,   626,   629,
     633,   637,   648,   650,   652,   656,   667,   669,   675,   685,
     698,   710,   720,   723,   733,   736,   746,   749,   759,   762,
     772,   775,   786,   789,   800,   803,   810,   819,   821,   828,
     837,   839,   845,   853,   856,   862,   871,   873,   875,   882,
     884,   886,   888,   890,   892,   896,   906,   908,   914,   916,
     920,   930,   933,   937,   939,   941,   945,   953,   955,   959,
     961,   963,   967,   969,   973,   978,   986,  1001,  1007,  1009,
    1012,  1016,  1022,  1032,  1036,  1041,  1047,  1066,  1068,  1074,
    1080,  1086
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
  "otherstmt", "compoundStmt", "localDeclarations", "statementList",
  "expressionStmt", "matched", "unmatched", "returnStmt", "breakStmt",
  "expression", "simpleExpression", "andExpression", "unaryRelExpression",
  "relExpression", "relop", "sumExpression", "sumop", "term", "mulop",
  "unaryExpression", "unaryop", "factor", "mutable", "immutable", "call",
  "args", "argList", "constant", 0
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
      75,    75,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    77,    77,    77,    77,    77,    77,    77,    78,    78,
      79,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    81,    81,    81,    82,
      82,    82,    83,    83,    83,    84,    84,    84,    84,    85,
      85,    85,    85,    85,    85,    86,    86,    86,    87,    87,
      88,    88,    88,    89,    89,    89,    90,    90,    90,    91,
      91,    91,    92,    92,    93,    93,    93,    94,    94,    94,
      94,    94,    95,    95,    96,    96,    97,    97,    97,    98,
      98,    98
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
       2,     1,     7,     3,     6,     5,     4,     5,     2,     1,
       1,     5,     2,     4,     6,     5,     4,     5,     2,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     1,     3,     3,     1,     3,
       3,     1,     2,     2,     1,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     3,     2,     2,
       1,     1,     4,     2,     1,     0,     3,     3,     1,     1,
       1,     1
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
      12,     0,    10,     0,   159,   160,   144,   161,     0,   141,
     140,   139,     0,    22,   108,   111,   114,   118,   127,   132,
       0,   138,   143,   142,   150,   151,    26,     0,    17,    16,
      23,    21,    49,    54,    48,    52,     0,     0,     0,    37,
       0,   123,   124,   119,   120,   122,   121,   153,   149,     0,
       0,   113,   112,   148,     0,   105,   143,     0,     0,   128,
     129,     0,     0,   133,   134,   135,     0,   137,   136,     0,
       0,    25,    56,     0,     0,    41,     0,     0,     0,     0,
       0,    71,    39,    79,    60,    59,    57,    58,    61,    62,
       0,    45,    44,     0,     0,     9,    66,     0,    29,     0,
       0,     0,   117,     0,   158,     0,   154,     0,     0,     0,
       0,   104,   102,     0,   147,     0,     0,     0,     0,   103,
     101,     0,   107,   106,   110,   109,   116,   115,   126,   125,
     131,   130,   146,     0,    55,    51,    50,    82,     0,    78,
       0,    88,     0,    90,    69,     0,    70,     0,    28,    19,
       0,    38,    80,    35,   152,     0,    94,    96,    98,   100,
      92,    93,    95,    97,    99,    91,   145,     0,    73,     0,
       0,     0,     0,    89,     0,     0,     0,    14,    15,    13,
     157,   156,    83,    57,     0,    76,    86,     0,     0,    64,
      68,    65,    63,     0,    81,    57,    77,    87,    85,    57,
      74,    84,     0,     0,     0,    72,     0,     0,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    10,    11,    12,   136,   187,    19,    20,
     137,    35,    14,    15,    36,    37,    38,    74,    75,   230,
     123,   124,    78,   214,   125,   126,   127,   128,   129,   130,
      95,    54,    55,    56,    89,    57,   102,    58,   106,    59,
      60,    61,    96,    63,    64,   145,   146,    65
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -201
static const yytype_int16 yypact[] =
{
     540,   715,   -23,  -201,    21,  -201,  -201,  -201,    32,   731,
    -201,  -201,  -201,    11,  -201,  -201,    65,    -3,    38,  -201,
      -2,   170,     4,  -201,  -201,   184,   221,   262,  -201,   107,
     329,   154,  -201,   321,   -20,   181,    25,    35,  -201,  -201,
    -201,    24,  -201,   721,  -201,  -201,    53,  -201,   368,  -201,
    -201,  -201,   421,    92,   111,  -201,  -201,   747,   213,  -201,
     587,  -201,    -7,  -201,  -201,  -201,  -201,    63,    65,  -201,
     721,    92,   158,    81,    88,  -201,   394,   734,   126,   132,
     255,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,   609,
      40,   721,  -201,   677,   128,    92,   656,   460,   499,  -201,
    -201,   628,   635,  -201,  -201,  -201,   654,   272,  -201,   148,
     511,  -201,  -201,   150,   229,   677,    13,    22,   274,   168,
      85,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,  -201,
     192,  -201,  -201,   285,   270,  -201,  -201,   287,  -201,   202,
     433,   272,   302,   677,  -201,   208,   216,   269,   279,   286,
     292,  -201,  -201,   299,  -201,   511,   511,   511,   511,  -201,
    -201,   511,   721,   111,   721,  -201,   272,   302,   272,   213,
     272,  -201,  -201,   273,  -201,   283,  -201,   264,   521,   301,
     560,  -201,   295,  -201,  -201,   253,  -201,   284,  -201,    98,
     288,  -201,   677,  -201,  -201,   568,  -201,  -201,  -201,  -201,
    -201,  -201,  -201,  -201,  -201,  -201,  -201,   433,   721,    54,
     433,   727,   115,  -201,   300,    16,   347,  -201,  -201,  -201,
     677,  -201,  -201,   317,   433,  -201,  -201,   159,   433,  -201,
    -201,  -201,  -201,   433,  -201,   330,  -201,  -201,  -201,   336,
    -201,  -201,   472,    33,    34,  -201,   314,   521,   316,   579,
     472,   119,   472,   741,   123,   343,   472,   206,   472,   472,
     330,  -201
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -201,  -201,  -201,   352,  -201,  -201,  -201,     7,   333,  -201,
    -201,     2,  -201,  -201,   337,  -201,   293,  -201,   260,   -70,
    -201,  -201,   257,   194,  -201,  -200,    -4,  -201,  -201,   -39,
     -28,   289,   -45,  -201,   323,    -6,  -201,   280,  -201,   -51,
    -201,  -201,   -29,  -201,  -201,  -201,  -201,  -201
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -156
static const yytype_int16 yytable[] =
{
      62,    53,    13,    92,    62,    71,   122,   223,    18,   108,
     225,    13,    25,    94,   177,   109,    26,    16,    21,    62,
      27,    17,   -47,   179,   235,    79,    22,   236,   239,   -47,
       3,    62,    23,   240,   246,   248,   110,     5,     6,     7,
      30,   143,   245,    44,    45,    46,    33,    47,    48,    39,
     255,   144,   225,   165,   178,   171,   260,   236,   261,   240,
      62,    49,   231,   180,    97,   -43,   -43,    76,    62,    62,
     193,   173,    62,    62,   247,   249,    50,    62,    51,   182,
     138,    52,  -155,   142,    77,    31,   184,    32,   -67,   -67,
     -67,   -67,   -67,   -67,    90,   167,   224,   -67,   -67,   -67,
     -67,   -67,    97,   -67,   -67,   -67,   -67,   111,    43,    28,
      44,    45,    46,    29,    47,    48,   201,   202,   203,   204,
      98,   -67,   205,   -67,   113,    97,   -67,   133,    49,    97,
     -67,   -67,     3,    97,   -67,   114,   188,   222,   134,     5,
       6,     7,    28,    50,   190,    51,    29,   218,    52,    62,
     209,    62,   212,   172,   234,    68,   221,   228,   238,    17,
     192,   256,    44,    45,    46,   258,    47,    48,  -149,  -149,
     154,    34,   135,   -47,   -47,   116,     3,   117,   118,   119,
      49,   -47,    72,     5,     6,     7,    73,   138,  -149,  -149,
    -149,  -149,  -149,  -149,   174,    50,  -149,    51,  -149,  -149,
      52,  -149,   112,   191,   120,   -53,   226,   192,   121,    44,
      45,    46,   -43,    47,    48,  -149,  -149,   183,    62,   251,
      62,   254,   243,   237,   244,   118,   119,    49,    28,   241,
     175,   -19,    29,    40,    73,  -149,  -149,  -149,  -149,  -149,
    -149,   186,    50,  -149,    51,  -149,  -149,    52,  -149,   103,
     194,   120,   104,   105,   215,   121,   -69,   -69,   -69,     3,
     -69,   -69,    41,   195,    30,   134,     5,     6,     7,   -69,
     196,   -69,   -69,   -69,   -69,   143,     3,    44,    45,    46,
     197,    47,    48,     5,     6,     7,    16,   198,   189,   -69,
      17,   -69,    17,   199,   -69,    49,   139,   140,   -69,   -69,
     200,   192,   -69,    44,    45,    46,   207,    47,    48,    31,
      50,    42,    51,    87,    88,    52,   116,   206,   117,   118,
     119,    49,    70,   181,    44,    45,    46,   112,    47,    48,
      66,    31,    67,   217,   233,    31,    50,   219,    51,    99,
     100,    52,    49,   210,   213,   120,   229,   242,   192,   121,
      44,    45,    46,   -75,    47,    48,   250,    50,   252,    51,
     259,    24,    52,   116,    69,   117,   118,   119,    49,    91,
     132,    44,    45,    46,   176,    47,    48,   185,    80,   216,
     101,     0,   169,    50,     0,    51,   163,     0,    52,    49,
       0,     0,   120,   232,     0,   115,   121,    44,    45,    46,
       0,    47,    48,     0,    50,     0,    51,     0,     0,    52,
     116,     0,   117,   118,   119,    49,     0,     0,     0,     0,
       0,     0,    93,     0,    44,    45,    46,     0,    47,    48,
      50,     0,    51,     0,   192,    52,    44,    45,    46,   120,
      47,    48,    49,   121,     0,     0,     0,     0,     0,   116,
       0,   117,   118,   119,    49,     0,     0,    50,     0,    51,
       0,   162,    52,    44,    45,    46,     0,    47,    48,    50,
       0,    51,     0,   192,    52,    44,    45,    46,   120,    47,
      48,    49,   121,     0,     0,     0,     0,     0,   243,     0,
     244,   118,   119,    49,     0,     0,    50,     0,    51,     0,
     164,    52,    44,    45,    46,     0,    47,    48,    50,     0,
      51,     0,   143,    52,    44,    45,    46,   120,    47,    48,
      49,   121,   208,     0,    44,    45,    46,     0,    47,    48,
       0,     0,    49,     0,     0,    50,     0,    51,     0,     0,
      52,     1,    49,     0,     0,     2,     3,    50,     0,    51,
       0,     4,    52,     5,     6,     7,     0,    50,     0,    51,
       0,   211,    52,    44,    45,    46,     0,    47,    48,   220,
       0,    44,    45,    46,     0,    47,    48,     0,     0,     0,
     253,    49,    44,    45,    46,     0,    47,    48,   107,    49,
      44,    45,    46,     0,    47,     0,    50,     0,    51,     0,
      49,    52,     0,     0,    50,     0,    51,     0,    49,    52,
     141,     0,    44,    45,    46,    50,    47,    51,     0,     0,
      52,     0,     0,    50,     0,    51,     0,     0,    52,   166,
      49,    44,    45,    46,     0,    47,   168,     0,    44,    45,
      46,     0,    47,     0,     0,    50,     0,    51,     0,    49,
      52,     0,     0,     0,     0,   170,    49,    44,    45,    46,
       0,    47,     0,     0,    50,     0,    51,     0,     0,    52,
       0,    50,     0,    51,     0,    49,    52,     0,   109,   155,
     156,   157,   158,   159,   160,     0,     0,     0,     0,     0,
      50,   161,    51,     0,     0,    52,     0,     0,     0,   110,
     147,   148,   149,   150,   151,   152,    81,    82,    83,    84,
      85,    86,   153,     0,     0,    -8,    16,     0,    87,    88,
      17,    -8,     0,     0,     0,     0,    -8,     0,    -8,    -8,
      -8,    -2,     1,     0,     0,   131,     2,     3,     0,     0,
       3,     0,     4,     0,     5,     6,     7,     5,     6,     7,
      81,    82,    83,    84,    85,    86,    81,    82,    83,    84,
      85,    86,    87,    88,     0,     0,     0,     0,    87,   227,
      81,    82,    83,    84,    85,    86,    81,    82,    83,    84,
      85,    86,    87,   257,    99,   100
};

static const yytype_int16 yycheck[] =
{
      29,    29,     0,    48,    33,    33,    76,   207,     1,    60,
     210,     9,     1,    52,     1,    22,     5,     1,    41,    48,
      13,     5,    42,     1,   224,     1,     5,   227,   228,    49,
       6,    60,     0,   233,     1,     1,    43,    13,    14,    15,
      43,     1,   242,     3,     4,     5,    48,     7,     8,    45,
     250,    90,   252,    98,    41,   106,   256,   257,   258,   259,
      89,    21,    46,    41,    10,    41,    42,    42,    97,    98,
     140,   110,   101,   102,    41,    41,    36,   106,    38,   118,
      78,    41,    42,    89,    49,    47,     1,    49,     3,     4,
       5,     6,     7,     8,    41,   101,    42,    12,    13,    14,
      15,    16,    10,    18,    19,    20,    21,    44,     1,    44,
       3,     4,     5,    48,     7,     8,   155,   156,   157,   158,
       9,    36,   161,    38,    43,    10,    41,     1,    21,    10,
      45,    46,     6,    10,    49,    47,   134,   207,    12,    13,
      14,    15,    44,    36,   137,    38,    48,    49,    41,   178,
     178,   180,   180,     5,   224,     1,   195,    42,   228,     5,
       1,    42,     3,     4,     5,    42,     7,     8,     9,    10,
      42,     1,    46,    41,    42,    16,     6,    18,    19,    20,
      21,    49,     1,    13,    14,    15,     5,   185,    29,    30,
      31,    32,    33,    34,    44,    36,    37,    38,    39,    40,
      41,    42,    44,     1,    45,    47,   210,     1,    49,     3,
       4,     5,    42,     7,     8,     9,    10,    49,   247,   247,
     249,   249,    16,   227,    18,    19,    20,    21,    44,   233,
       1,    47,    48,    49,     5,    29,    30,    31,    32,    33,
      34,    49,    36,    37,    38,    39,    40,    41,    42,    36,
      42,    45,    39,    40,     1,    49,     3,     4,     5,     6,
       7,     8,    41,    47,    43,    12,    13,    14,    15,    16,
       1,    18,    19,    20,    21,     1,     6,     3,     4,     5,
       1,     7,     8,    13,    14,    15,     1,     1,     1,    36,
       5,    38,     5,     1,    41,    21,    41,    42,    45,    46,
       1,     1,    49,     3,     4,     5,    42,     7,     8,    47,
      36,    49,    38,    41,    42,    41,    16,    44,    18,    19,
      20,    21,     1,    49,     3,     4,     5,    44,     7,     8,
       1,    47,     3,    49,    17,    47,    36,    49,    38,    37,
      38,    41,    21,    42,    49,    45,    46,    17,     1,    49,
       3,     4,     5,    17,     7,     8,    42,    36,    42,    38,
      17,     9,    41,    16,    31,    18,    19,    20,    21,     1,
      77,     3,     4,     5,   114,     7,     8,   120,    41,   185,
      57,    -1,   102,    36,    -1,    38,    97,    -1,    41,    21,
      -1,    -1,    45,    46,    -1,     1,    49,     3,     4,     5,
      -1,     7,     8,    -1,    36,    -1,    38,    -1,    -1,    41,
      16,    -1,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,     3,     4,     5,    -1,     7,     8,
      36,    -1,    38,    -1,     1,    41,     3,     4,     5,    45,
       7,     8,    21,    49,    -1,    -1,    -1,    -1,    -1,    16,
      -1,    18,    19,    20,    21,    -1,    -1,    36,    -1,    38,
      -1,     1,    41,     3,     4,     5,    -1,     7,     8,    36,
      -1,    38,    -1,     1,    41,     3,     4,     5,    45,     7,
       8,    21,    49,    -1,    -1,    -1,    -1,    -1,    16,    -1,
      18,    19,    20,    21,    -1,    -1,    36,    -1,    38,    -1,
       1,    41,     3,     4,     5,    -1,     7,     8,    36,    -1,
      38,    -1,     1,    41,     3,     4,     5,    45,     7,     8,
      21,    49,     1,    -1,     3,     4,     5,    -1,     7,     8,
      -1,    -1,    21,    -1,    -1,    36,    -1,    38,    -1,    -1,
      41,     1,    21,    -1,    -1,     5,     6,    36,    -1,    38,
      -1,    11,    41,    13,    14,    15,    -1,    36,    -1,    38,
      -1,     1,    41,     3,     4,     5,    -1,     7,     8,     1,
      -1,     3,     4,     5,    -1,     7,     8,    -1,    -1,    -1,
       1,    21,     3,     4,     5,    -1,     7,     8,     1,    21,
       3,     4,     5,    -1,     7,    -1,    36,    -1,    38,    -1,
      21,    41,    -1,    -1,    36,    -1,    38,    -1,    21,    41,
       1,    -1,     3,     4,     5,    36,     7,    38,    -1,    -1,
      41,    -1,    -1,    36,    -1,    38,    -1,    -1,    41,     1,
      21,     3,     4,     5,    -1,     7,     1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    36,    -1,    38,    -1,    21,
      41,    -1,    -1,    -1,    -1,     1,    21,     3,     4,     5,
      -1,     7,    -1,    -1,    36,    -1,    38,    -1,    -1,    41,
      -1,    36,    -1,    38,    -1,    21,    41,    -1,    22,    23,
      24,    25,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      36,    35,    38,    -1,    -1,    41,    -1,    -1,    -1,    43,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    -1,     0,     1,    -1,    41,    42,
       5,     6,    -1,    -1,    -1,    -1,    11,    -1,    13,    14,
      15,     0,     1,    -1,    -1,     1,     5,     6,    -1,    -1,
       6,    -1,    11,    -1,    13,    14,    15,    13,    14,    15,
      29,    30,    31,    32,    33,    34,    29,    30,    31,    32,
      33,    34,    41,    42,    -1,    -1,    -1,    -1,    41,    42,
      29,    30,    31,    32,    33,    34,    29,    30,    31,    32,
      33,    34,    41,    42,    37,    38
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
      36,    38,    41,    81,    82,    83,    84,    86,    88,    90,
      91,    92,    93,    94,    95,    98,     1,     3,     1,    59,
       1,    81,     1,     5,    68,    69,    42,    49,    73,     1,
      65,    29,    30,    31,    32,    33,    34,    41,    42,    85,
      41,     1,    83,     1,    80,    81,    93,    10,     9,    37,
      38,    85,    87,    36,    39,    40,    89,     1,    90,    22,
      43,    44,    44,    43,    47,     1,    16,    18,    19,    20,
      45,    49,    70,    71,    72,    75,    76,    77,    78,    79,
      80,     1,    67,     1,    12,    46,    57,    61,    62,    41,
      42,     1,    86,     1,    80,    96,    97,    23,    24,    25,
      26,    27,    28,    35,    42,    23,    24,    25,    26,    27,
      28,    35,     1,    82,     1,    83,     1,    86,     1,    88,
       1,    90,     5,    80,    44,     1,    69,     1,    41,     1,
      41,    49,    80,    49,     1,    73,    49,    58,    62,     1,
      58,     1,     1,    70,    42,    47,     1,     1,     1,     1,
       1,    80,    80,    80,    80,    80,    44,    42,     1,    81,
      42,     1,    81,    49,    74,     1,    74,    49,    49,    49,
       1,    80,    70,    76,    42,    76,    77,    42,    42,    46,
      70,    46,    46,    17,    70,    76,    76,    77,    70,    76,
      76,    77,    17,    16,    18,    76,     1,    41,     1,    41,
      42,    81,    42,     1,    81,    76,    42,    42,    42,    17,
      76,    76
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

  case 8:
#line 156 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 9:
#line 160 "parser.y"
    {

								(yyval.treeNode) = newDeclNode(recDeclaration);
								(yyval.treeNode) -> isRecord = true;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (5)].tokenData) -> lineno;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (5)].tokenData) -> tokenString);
								//symTab.insert($$ -> attr.name, (char *)"RECORD");
								//st.print(pointerPrintStr); 
								(yyval.treeNode) -> child[0] = (yyvsp[(4) - (5)].treeNode);
								(yyval.treeNode) -> numChildren = 1;
								
							;}
    break;

  case 10:
#line 175 "parser.y"
    {
								yyerrok;
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
								
 							;}
    break;

  case 11:
#line 193 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 12:
#line 195 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 13:
#line 199 "parser.y"
    {
								yyerrok;
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
								
							;}
    break;

  case 14:
#line 219 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 15:
#line 221 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 16:
#line 225 "parser.y"
    {
								yyerrok;
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
								
							;}
    break;

  case 17:
#line 246 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 18:
#line 249 "parser.y"
    { 
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); 
							;}
    break;

  case 19:
#line 253 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 20:
#line 257 "parser.y"
    {	
 								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 21:
#line 261 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[0] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 1;
								
							;}
    break;

  case 22:
#line 268 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 23:
#line 270 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 24:
#line 275 "parser.y"
    {
								(yyval.treeNode) = newDeclNode(varDeclaration);
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(1) - (1)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (1)].tokenData) -> lineno;
								(yyval.treeNode)->isArray = false;
								//$$ -> isStatic = isStatic;
							;}
    break;

  case 25:
#line 283 "parser.y"
    {

								(yyval.treeNode) = newDeclNode(varDeclaration);
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(1) - (4)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (4)].tokenData) -> lineno;
								(yyval.treeNode)->isArray = true; 
								(yyval.treeNode)->arrLen = (yyvsp[(3) - (4)].tokenData) -> numVal;
								//$$ -> isStatic = isStatic;
							;}
    break;

  case 26:
#line 293 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 27:
#line 295 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 28:
#line 300 "parser.y"
    {
								(yyval.treeNode) = newDeclNode(varDeclaration);
								(yyval.treeNode) -> isStatic = true;
								(yyval.treeNode) -> type = (yyvsp[(2) - (2)].expType);
							;}
    break;

  case 29:
#line 306 "parser.y"
    { 
								(yyval.treeNode) = newDeclNode(varDeclaration);
								(yyval.treeNode) -> type = (yyvsp[(1) - (1)].expType);
							;}
    break;

  case 30:
#line 313 "parser.y"
    {
								(yyval.expType) = (yyvsp[(1) - (1)].expType);
							;}
    break;

  case 31:
#line 318 "parser.y"
    {
								(yyval.expType)  = record; 
							;}
    break;

  case 32:
#line 324 "parser.y"
    {
								(yyval.expType) = integer;	
							;}
    break;

  case 33:
#line 328 "parser.y"
    {
								(yyval.expType) = boolean; 
							;}
    break;

  case 34:
#line 332 "parser.y"
    {
								(yyval.expType) = character;
							;}
    break;

  case 35:
#line 338 "parser.y"
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

  case 36:
#line 349 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 37:
#line 351 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 38:
#line 353 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 39:
#line 356 "parser.y"
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

  case 40:
#line 366 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 41:
#line 368 "parser.y"
    { (yyval.treeNode) = NULL;;}
    break;

  case 42:
#line 373 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 43:
#line 377 "parser.y"
    {
								(yyval.treeNode) = NULL;
							;}
    break;

  case 44:
#line 383 "parser.y"
    {
								yyerrok;
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
								
							;}
    break;

  case 46:
#line 406 "parser.y"
    { 
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); 
							;}
    break;

  case 47:
#line 410 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 48:
#line 415 "parser.y"
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

  case 49:
#line 432 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 50:
#line 436 "parser.y"
    {
								yyerrok;
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
								
							;}
    break;

  case 51:
#line 457 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 52:
#line 460 "parser.y"
    { 
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); 
							;}
    break;

  case 53:
#line 465 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 54:
#line 469 "parser.y"
    {
								(yyval.treeNode) = newDeclNode(paramDeclaration); 
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(1) - (1)].tokenData) -> tokenString);
								(yyval.treeNode)->isArray = false;
								(yyval.treeNode)->isParam = true;
							;}
    break;

  case 55:
#line 476 "parser.y"
    {
								(yyval.treeNode) = newDeclNode(paramDeclaration);
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(1) - (3)].tokenData) -> tokenString);
								(yyval.treeNode)->isArray = true;
								(yyval.treeNode)->isParam = true;
							;}
    break;

  case 56:
#line 483 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 57:
#line 488 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 58:
#line 490 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 59:
#line 494 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 60:
#line 496 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 61:
#line 498 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 62:
#line 500 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 63:
#line 504 "parser.y"
    {
								yyerrok;
								(yyval.treeNode) = newStmtNode(compoundStmt); 
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (4)].tokenData) -> lineno;
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> child[0] = (yyvsp[(2) - (4)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (4)].treeNode); 

								//TODO: Remove this, enter new scope for compoundStmt
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (4)].tokenData) -> tokenString; 
								(yyval.treeNode) -> type = Void;

								
							;}
    break;

  case 64:
#line 519 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 65:
#line 521 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 66:
#line 525 "parser.y"
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
#line 544 "parser.y"
    {
								(yyval.treeNode) = NULL;
							;}
    break;

  case 68:
#line 550 "parser.y"
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
#line 569 "parser.y"
    {
								(yyval.treeNode) = NULL;
							;}
    break;

  case 70:
#line 576 "parser.y"
    {
								yyerrok;
								(yyval.treeNode) = (yyvsp[(1) - (2)].treeNode);

							;}
    break;

  case 71:
#line 583 "parser.y"
    {
								yyerrok;
								(yyval.treeNode) = NULL;
								
							;}
    break;

  case 72:
#line 594 "parser.y"
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

  case 73:
#line 606 "parser.y"
    { (yyval.treeNode) = NULL;;}
    break;

  case 74:
#line 608 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 75:
#line 612 "parser.y"
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

  case 76:
#line 623 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 77:
#line 625 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 78:
#line 627 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 79:
#line 630 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 80:
#line 634 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 81:
#line 638 "parser.y"
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

  case 82:
#line 649 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 83:
#line 651 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 84:
#line 653 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 85:
#line 657 "parser.y"
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

  case 86:
#line 668 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 87:
#line 670 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 88:
#line 676 "parser.y"
    {   
								yyerrok;
								(yyval.treeNode) = newStmtNode(returnStmt); 
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (2)].tokenData) -> tokenString;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (2)].tokenData) -> lineno;
								(yyval.treeNode) -> type = Void;

								
							;}
    break;

  case 89:
#line 686 "parser.y"
    { 	
								yyerrok;
								(yyval.treeNode) = newStmtNode(returnStmt);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (3)].tokenData) -> tokenString;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (3)].tokenData) -> lineno;
								(yyval.treeNode) -> child[0] = (yyvsp[(2) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 1;
								(yyval.treeNode) -> type = Void;
								
							;}
    break;

  case 90:
#line 699 "parser.y"
    {	
								yyerrok;
								(yyval.treeNode) = newStmtNode(breakStmt);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (2)].tokenData) -> tokenString;
								(yyval.treeNode) -> type = Void;
								
							;}
    break;

  case 91:
#line 711 "parser.y"
    {
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].tokenData) -> lineno;
							;}
    break;

  case 92:
#line 721 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 93:
#line 724 "parser.y"
    {
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].tokenData) -> lineno;
							;}
    break;

  case 94:
#line 734 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 95:
#line 737 "parser.y"
    {
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].tokenData) -> lineno;
							;}
    break;

  case 96:
#line 747 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 97:
#line 750 "parser.y"
    {
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].tokenData) -> lineno;
							;}
    break;

  case 98:
#line 760 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 99:
#line 763 "parser.y"
    {
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].tokenData) -> lineno;
							;}
    break;

  case 100:
#line 773 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 101:
#line 776 "parser.y"
    {	
								yyerrok;
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (2)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (2)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (2)].tokenData) -> lineno;
								
							;}
    break;

  case 102:
#line 787 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 103:
#line 790 "parser.y"
    {
								yyerrok;
								(yyval.treeNode) = newExpNode(AssK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (2)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (2)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (2)].tokenData) -> lineno;
								
							;}
    break;

  case 104:
#line 801 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 105:
#line 804 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 106:
#line 811 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].tokenData) -> lineno;
							;}
    break;

  case 107:
#line 820 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 108:
#line 822 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 109:
#line 829 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].tokenData) -> tokenString);
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].tokenData) -> lineno;
						;}
    break;

  case 110:
#line 838 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 111:
#line 840 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 112:
#line 846 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(2) - (2)].treeNode);
								(yyval.treeNode) -> numChildren = 1;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(1) - (2)].tokenData) -> tokenString);
							;}
    break;

  case 113:
#line 854 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 114:
#line 857 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 115:
#line 863 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (3)].td) -> tokenString);
							;}
    break;

  case 116:
#line 872 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 117:
#line 874 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 118:
#line 876 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 119:
#line 883 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 120:
#line 885 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 121:
#line 887 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 122:
#line 889 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 123:
#line 891 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 124:
#line 893 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 125:
#line 897 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].td) -> tokenString;
								(yyval.treeNode) -> lineno = (yyvsp[(2) - (3)].td) -> lineno;
							;}
    break;

  case 126:
#line 907 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 127:
#line 909 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 128:
#line 915 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 129:
#line 917 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 130:
#line 921 "parser.y"
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
#line 931 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 132:
#line 934 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 133:
#line 938 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 134:
#line 940 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 135:
#line 942 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 136:
#line 946 "parser.y"
    {	
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(2) - (2)].treeNode);
								(yyval.treeNode) -> numChildren = 1;
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (2)].td) -> tokenString;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (2)].td) -> lineno;
							;}
    break;

  case 137:
#line 954 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 138:
#line 956 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 139:
#line 960 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 140:
#line 962 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 141:
#line 964 "parser.y"
    {(yyval.td) = (yyvsp[(1) - (1)].tokenData);;}
    break;

  case 142:
#line 968 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 143:
#line 970 "parser.y"
    {(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);;}
    break;

  case 144:
#line 974 "parser.y"
    {
								(yyval.treeNode) = newExpNode(IdK);
								(yyval.treeNode) -> attr.name = (yyvsp[(1) - (1)].tokenData) -> tokenString;
							;}
    break;

  case 145:
#line 979 "parser.y"
    {
								(yyval.treeNode) = newExpNode(OpK);
								(yyval.treeNode) -> child[0] = (yyvsp[(1) - (4)].treeNode);
								(yyval.treeNode) -> child[1] = (yyvsp[(3) - (4)].treeNode);
								(yyval.treeNode) -> numChildren = 2;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(2) - (4)].tokenData) -> tokenString);
							;}
    break;

  case 146:
#line 987 "parser.y"
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

  case 147:
#line 1002 "parser.y"
    {	
								(yyval.treeNode) = (yyvsp[(2) - (3)].treeNode);
								yyerrok;
							;}
    break;

  case 148:
#line 1008 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 149:
#line 1010 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 150:
#line 1013 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 151:
#line 1017 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 152:
#line 1023 "parser.y"
    {
								(yyval.treeNode) = newExpNode(CallK);
								(yyval.treeNode) -> child[0] = (yyvsp[(3) - (4)].treeNode);
								(yyval.treeNode) -> numChildren = 1;
								(yyval.treeNode) -> attr.name = strdup((yyvsp[(1) - (4)].tokenData) -> tokenString);
								(yyval.treeNode) ->isArray = false;
								(yyval.treeNode) -> lineno = (yyvsp[(1) - (4)].tokenData) -> lineno;

							;}
    break;

  case 153:
#line 1033 "parser.y"
    {yyerrok; (yyval.treeNode) = NULL;;}
    break;

  case 154:
#line 1037 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 155:
#line 1041 "parser.y"
    {
								(yyval.treeNode) = NULL;
							;}
    break;

  case 156:
#line 1048 "parser.y"
    {
								yyerrok;
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
								
							;}
    break;

  case 157:
#line 1067 "parser.y"
    {(yyval.treeNode) = NULL;;}
    break;

  case 158:
#line 1069 "parser.y"
    {
								(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
							;}
    break;

  case 159:
#line 1075 "parser.y"
    {
								(yyval.treeNode) = newExpNode(constK);
								(yyval.treeNode) ->attr.value = (yyvsp[(1) - (1)].tokenData)->numVal;
								(yyval.treeNode) -> type = integer;
							;}
    break;

  case 160:
#line 1081 "parser.y"
    {
								(yyval.treeNode) = newExpNode(constK);
								(yyval.treeNode) ->attr.cvalue = (yyvsp[(1) - (1)].tokenData)->charVal;
								(yyval.treeNode) -> type = character;
							;}
    break;

  case 161:
#line 1087 "parser.y"
    {
								(yyval.treeNode) = newExpNode(constK);
								(yyval.treeNode) -> attr.bvalue = (yyvsp[(1) - (1)].tokenData)->bvalue;
								(yyval.treeNode) -> type = boolean;
							;}
    break;


/* Line 1267 of yacc.c.  */
#line 3146 "parser.tab.c"
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


#line 1094 "parser.y"


int main(int argc, char *argv[])
{

	extern int yydebug;
	int optCount = 1;
	int printingTree = 0;
	numWarnings = 0;
	numErrors = 0;
	bool syntaxErrors = false;

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

	if (numErrors != 0)
	{
		syntaxErrors = true;
	}
	
	savedTree = setup(setupTree, savedTree);

	// print -p before errors
	if (printingTree == 1 && !capP) //1)
	{
		printTree(savedTree, capP);
	}


	if(!syntaxErrors)
	{
		scopeAndTypeR(savedTree);
	}
	

	if(symTab.lookup("main") == NULL && !syntaxErrors)
	{
		printError(-2, 0, NULL, 0, na, na, 0);
	}

	/* Symtab printing stuff 
	//symTab.print(pointerPrintStr);
	//finalSymTab = getSymTab();
	//finalSymTab.print(pointerPrintStr);
	*/

	// print -P w types after errors
	if (printingTree == 1 && capP && !syntaxErrors) //1)
	{
		printTree(savedTree, capP);
	}

	if(!syntaxErrors) printf("Offset for end of global space: %d\n", getGlobalOff());
	printf("Number of warnings: %d\n", numWarnings);
	printf("Number of errors: %d\n", numErrors);
	//symTab.print(pointerPrintStr);

	return 0;
}

