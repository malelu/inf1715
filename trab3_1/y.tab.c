/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 2 "analisadorSintatico.y"

#include "ast.h"
#include "token.h"

AST* programa ;



/* Line 268 of yacc.c  */
#line 80 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_CHAR = 258,
     TK_INT = 259,
     TK_STRING = 260,
     TK_BOOL = 261,
     TK_TRUE = 262,
     TK_FALSE = 263,
     TK_NOT = 264,
     TK_WHILE = 265,
     TK_LOOP = 266,
     TK_IF = 267,
     TK_ELSE = 268,
     TK_END = 269,
     TK_NEW = 270,
     TK_RET = 271,
     TK_FUN = 272,
     TK_GREATER_EQUAL = 273,
     TK_LESS_EQUAL = 274,
     TK_NOT_EQUAL = 275,
     TK_AND = 276,
     TK_OR = 277,
     TK_NUMINT = 278,
     TK_ID = 279,
     TK_LITERAL_STRING = 280,
     TK_LINE = 281,
     ERROR = 282
   };
#endif
/* Tokens.  */
#define TK_CHAR 258
#define TK_INT 259
#define TK_STRING 260
#define TK_BOOL 261
#define TK_TRUE 262
#define TK_FALSE 263
#define TK_NOT 264
#define TK_WHILE 265
#define TK_LOOP 266
#define TK_IF 267
#define TK_ELSE 268
#define TK_END 269
#define TK_NEW 270
#define TK_RET 271
#define TK_FUN 272
#define TK_GREATER_EQUAL 273
#define TK_LESS_EQUAL 274
#define TK_NOT_EQUAL 275
#define TK_AND 276
#define TK_OR 277
#define TK_NUMINT 278
#define TK_ID 279
#define TK_LITERAL_STRING 280
#define TK_LINE 281
#define ERROR 282




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 176 "y.tab.c"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   144

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  152

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   282

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      29,    30,    39,    37,    31,    38,     2,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    28,     2,
      35,    34,    36,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,    10,    12,    14,    19,    20,    23,
      35,    45,    46,    49,    50,    54,    58,    64,    68,    69,
      71,    75,    77,    79,    81,    83,    84,    88,    90,    92,
      94,    96,    98,   105,   112,   116,   117,   123,   127,   129,
     134,   139,   140,   143,   144,   148,   151,   153,   155,   158,
     160,   162,   166,   168,   172,   174,   178,   182,   186,   190,
     194,   198,   200,   204,   208,   210,   214,   218,   221,   224,
     226,   228,   230,   232,   234,   240,   245,   247
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      42,     0,    -1,    43,    45,    -1,    64,    43,    45,    -1,
      46,    -1,    44,    -1,    24,    28,    51,    64,    -1,    -1,
      43,    45,    -1,    17,    24,    29,    47,    30,    28,    51,
      64,    50,    14,    64,    -1,    17,    24,    29,    47,    30,
      64,    50,    14,    64,    -1,    -1,    49,    48,    -1,    -1,
      48,    31,    49,    -1,    24,    28,    51,    -1,    24,    28,
      51,    64,    50,    -1,    54,    64,    53,    -1,    -1,    52,
      -1,    32,    33,    51,    -1,     4,    -1,     3,    -1,     6,
      -1,     5,    -1,    -1,    54,    64,    53,    -1,    55,    -1,
      57,    -1,    58,    -1,    63,    -1,    60,    -1,    12,    65,
      64,    50,    56,    14,    -1,    13,    12,    65,    64,    50,
      56,    -1,    13,    64,    50,    -1,    -1,    10,    65,    64,
      50,    11,    -1,    59,    34,    65,    -1,    24,    -1,    59,
      32,    65,    33,    -1,    24,    29,    61,    30,    -1,    -1,
      65,    62,    -1,    -1,    31,    65,    62,    -1,    16,    65,
      -1,    16,    -1,    26,    -1,    26,    64,    -1,    66,    -1,
      67,    -1,    66,    22,    67,    -1,    68,    -1,    67,    21,
      68,    -1,    69,    -1,    68,    35,    69,    -1,    68,    36,
      69,    -1,    68,    34,    69,    -1,    68,    19,    69,    -1,
      68,    18,    69,    -1,    68,    20,    69,    -1,    70,    -1,
      69,    37,    70,    -1,    69,    38,    70,    -1,    71,    -1,
      70,    39,    71,    -1,    70,    40,    71,    -1,     9,    71,
      -1,    38,    71,    -1,    72,    -1,    23,    -1,    25,    -1,
       7,    -1,     8,    -1,    15,    32,    65,    33,    51,    -1,
      24,    29,    61,    30,    -1,    59,    -1,    29,    65,    30,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    38,    38,    47,    51,    52,    54,    58,    59,    61,
      82,   101,   103,   108,   109,   111,   115,   123,   127,   129,
     132,   134,   136,   137,   138,   140,   141,   143,   144,   145,
     146,   147,   150,   162,   172,   177,   179,   187,   191,   192,
     194,   199,   200,   202,   203,   205,   207,   209,   210,   212,
     214,   215,   219,   220,   224,   225,   229,   233,   237,   241,
     245,   249,   250,   254,   258,   259,   263,   267,   270,   273,
     275,   276,   277,   278,   279,   283,   286,   287
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_CHAR", "TK_INT", "TK_STRING",
  "TK_BOOL", "TK_TRUE", "TK_FALSE", "TK_NOT", "TK_WHILE", "TK_LOOP",
  "TK_IF", "TK_ELSE", "TK_END", "TK_NEW", "TK_RET", "TK_FUN",
  "TK_GREATER_EQUAL", "TK_LESS_EQUAL", "TK_NOT_EQUAL", "TK_AND", "TK_OR",
  "TK_NUMINT", "TK_ID", "TK_LITERAL_STRING", "TK_LINE", "ERROR", "':'",
  "'('", "')'", "','", "'['", "']'", "'='", "'<'", "'>'", "'+'", "'-'",
  "'*'", "'/'", "$accept", "programa", "decl", "global", "lista_decl",
  "funcao", "params", "lista_parametro", "parametro", "entradas", "tipo",
  "tipobase", "lista_comando", "comando", "cmdif", "entradas_else",
  "cmdwhile", "cmdatrib", "var", "chamada", "lista_exp", "sublista_exp",
  "cmdreturn", "nl", "exp", "exp_or", "exp_and", "exp_less", "exp_add",
  "exp_times", "exp_un", "exp_fin", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    58,    40,
      41,    44,    91,    93,    61,    60,    62,    43,    45,    42,
      47
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    42,    43,    43,    44,    45,    45,    46,
      46,    47,    47,    48,    48,    49,    50,    50,    50,    51,
      51,    52,    52,    52,    52,    53,    53,    54,    54,    54,
      54,    54,    55,    56,    56,    56,    57,    58,    59,    59,
      60,    61,    61,    62,    62,    63,    63,    64,    64,    65,
      66,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    69,    69,    69,    70,    70,    70,    71,    71,    71,
      72,    72,    72,    72,    72,    72,    72,    72
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     1,     1,     4,     0,     2,    11,
       9,     0,     2,     0,     3,     3,     5,     3,     0,     1,
       3,     1,     1,     1,     1,     0,     3,     1,     1,     1,
       1,     1,     6,     6,     3,     0,     5,     3,     1,     4,
       4,     0,     2,     0,     3,     2,     1,     1,     2,     1,
       1,     3,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     2,     2,     1,
       1,     1,     1,     1,     5,     4,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    47,     0,     7,     5,     4,     0,     0,
       0,    48,     1,     7,     2,     7,    11,    22,    21,    24,
      23,     0,     0,    19,     8,     3,     0,     0,    13,     0,
       6,     0,     0,    12,    20,    15,     0,    18,     0,     0,
       0,     0,    46,    38,     0,     0,    27,    28,    29,     0,
      31,    30,    14,    18,    72,    73,     0,     0,    70,    38,
      71,     0,     0,    76,     0,    49,    50,    52,    54,    61,
      64,    69,     0,    45,     0,    41,     0,    25,     0,     0,
       0,    67,     0,    41,     0,    68,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
       0,     0,    43,    10,    38,    17,     0,     0,    37,     0,
       0,     0,    77,     0,    51,    53,    59,    58,    60,    57,
      55,    56,    62,    63,    65,    66,    35,    18,    40,     0,
      42,    25,    39,     9,     0,    75,    36,     0,     0,    16,
      43,    26,    74,     0,    18,    32,    44,     0,    34,    18,
      35,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,    13,     6,    14,     7,    27,    33,    28,    44,
      22,    23,   105,    45,    46,   138,    47,    48,    63,    50,
     101,   130,    51,     8,   102,    65,    66,    67,    68,    69,
      70,    71
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -75
static const yytype_int8 yypact[] =
{
      51,    -9,    -7,     5,    37,    22,   -75,   -75,    22,    11,
      20,   -75,   -75,    22,   -75,    22,    35,   -75,   -75,   -75,
     -75,    34,     5,   -75,   -75,   -75,    16,    42,   -75,    20,
     -75,    20,    17,    45,   -75,   -75,    20,    -4,    35,     5,
     102,   102,   102,   -18,    64,     5,   -75,   -75,   -75,    24,
     -75,   -75,   -75,    -4,   -75,   -75,   102,    60,   -75,    69,
     -75,   102,   102,    67,     5,    78,    81,    46,    52,    15,
     -75,   -75,     5,   -75,    20,   102,     5,     6,   102,   102,
      90,   -75,   102,   102,    75,   -75,    -4,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,    -4,
       5,    82,    83,   -75,    86,   -75,     5,    85,   -75,     5,
      87,    89,   -75,   105,    81,    46,    52,    52,    52,    52,
      52,    52,    15,    15,   -75,   -75,   109,    -4,   -75,   102,
     -75,     6,   -75,   -75,    20,   -75,   -75,     2,   110,   -75,
      83,   -75,   -75,   102,    -4,   -75,   -75,     5,   -75,    -4,
     109,   -75
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -75,   -75,    27,   -75,    47,   -75,   -75,   -75,    91,   -48,
     -27,   -75,    -1,   -74,   -75,   -22,   -75,   -75,   -36,   -75,
      40,     1,   -75,    -3,    -8,   -75,    49,    44,    -6,    -2,
     -49,   -75
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      11,    49,    34,   106,    35,    80,    40,    81,    41,    39,
      74,    75,    42,    85,   143,     9,    40,    49,    41,    30,
      43,    10,    42,    17,    18,    19,    20,     5,     3,    37,
     104,     3,    64,    72,    73,    15,    53,    12,   113,     1,
      16,    49,    77,     3,    31,    36,     2,   100,   124,   125,
      49,   126,    21,    84,    97,    98,    78,   106,    79,    26,
      24,    86,    25,    49,    89,    90,    91,    29,     1,    99,
     107,   108,    32,   103,   110,     2,    38,     3,    76,   139,
      92,    93,    94,   116,   117,   118,   119,   120,   121,    95,
      96,    49,    82,   122,   123,    49,   148,   127,    83,    78,
      87,   150,    88,   131,   109,   112,   133,   142,    49,    54,
      55,    56,   128,    49,   129,    75,   136,    57,   132,   135,
     134,   140,   137,   111,   145,    58,    59,    60,   151,    52,
     141,    61,   115,     0,   144,   147,   114,     0,     0,     0,
      62,   146,     0,     0,   149
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-75))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       3,    37,    29,    77,    31,    53,    10,    56,    12,    36,
      28,    29,    16,    62,    12,    24,    10,    53,    12,    22,
      24,    28,    16,     3,     4,     5,     6,     0,    26,    32,
      24,    26,    40,    41,    42,     8,    39,     0,    86,    17,
      29,    77,    45,    26,    28,    28,    24,    74,    97,    98,
      86,    99,    32,    61,    39,    40,    32,   131,    34,    24,
      13,    64,    15,    99,    18,    19,    20,    33,    17,    72,
      78,    79,    30,    76,    82,    24,    31,    26,    14,   127,
      34,    35,    36,    89,    90,    91,    92,    93,    94,    37,
      38,   127,    32,    95,    96,   131,   144,   100,    29,    32,
      22,   149,    21,   106,    14,    30,   109,   134,   144,     7,
       8,     9,    30,   149,    31,    29,    11,    15,    33,    30,
      33,   129,    13,    83,    14,    23,    24,    25,   150,    38,
     131,    29,    88,    -1,   137,   143,    87,    -1,    -1,    -1,
      38,   140,    -1,    -1,   147
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    24,    26,    42,    43,    44,    46,    64,    24,
      28,    64,     0,    43,    45,    43,    29,     3,     4,     5,
       6,    32,    51,    52,    45,    45,    24,    47,    49,    33,
      64,    28,    30,    48,    51,    51,    28,    64,    31,    51,
      10,    12,    16,    24,    50,    54,    55,    57,    58,    59,
      60,    63,    49,    64,     7,     8,     9,    15,    23,    24,
      25,    29,    38,    59,    65,    66,    67,    68,    69,    70,
      71,    72,    65,    65,    28,    29,    14,    64,    32,    34,
      50,    71,    32,    29,    65,    71,    64,    22,    21,    18,
      19,    20,    34,    35,    36,    37,    38,    39,    40,    64,
      51,    61,    65,    64,    24,    53,    54,    65,    65,    14,
      65,    61,    30,    50,    67,    68,    69,    69,    69,    69,
      69,    69,    70,    70,    71,    71,    50,    64,    30,    31,
      62,    64,    33,    64,    33,    30,    11,    13,    56,    50,
      65,    53,    51,    12,    64,    14,    62,    65,    50,    64,
      50,    56
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1806 of yacc.c  */
#line 38 "analisadorSintatico.y"
    { programa = AST_new(AST_PROGRAM, 1);
						//fprintf(stderr, "ooooo\n");
						//fprintf(stderr, "decl    %d\n", $1.node);
						  AST_addChild(programa, (yyvsp[(1) - (2)]).node);
						/*fprintf(stderr, "$$->    %d\n", programa->firstChild);
						fprintf(stderr, "$$->    %d\n", programa->lastChild);
						fprintf(stderr, "lista_decl    %d\n", $2.node);*/
						  AST_addChildren(programa, (yyvsp[(2) - (2)]).node); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 47 "analisadorSintatico.y"
    { programa = AST_new(AST_PROGRAM, 1);
						  AST_addChild(programa, (yyvsp[(1) - (3)]).node);
						  AST_addChildren(programa, (yyvsp[(2) - (3)]).node); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 51 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 52 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 54 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_GLOBAL, (yyvsp[(1) - (4)]).line);
 						  AST_addChild((yyval).node, AST_newStringFromToken((yyvsp[(1) - (4)]).cValue, (yyvsp[(1) - (4)]).line));
						  AST_addChild((yyval).node, (yyvsp[(3) - (4)]).node); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 58 "analisadorSintatico.y"
    { (yyval).node = NULL; }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 59 "analisadorSintatico.y"
    { (yyval).node = AST_prependSibling((yyvsp[(2) - (2)]).node, (yyvsp[(1) - (2)]).node); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 63 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_FUN, (yyvsp[(1) - (11)]).line);
						  (yyval).node->stringVal = (yyvsp[(2) - (11)]).cValue ;
						  AST_addChild((yyval).node, (yyvsp[(7) - (11)]).node);
						  AST_addChild((yyval).node, (yyvsp[(4) - (11)]).node);
						  AST* block = AST_new(AST_BLOCK, (yyvsp[(9) - (11)]).line);
						  AST_addChildren(block, (yyvsp[(9) - (11)]).node);
					  	  AST_addChild((yyval).node, block);
						/*fprintf(stderr, "FUN\n");					  
						fprintf(stderr, "string    %s\n", $2.cValue);
						fprintf(stderr, "tipo    %d\n", $7.node);
						fprintf(stderr, "%d\n", $$.node);
						fprintf(stderr, "%d\n", $4.node);  
						fprintf(stderr, "block   %d\n", block);*/
						  AST_prependSibling((yyvsp[(7) - (11)]).node, (yyvsp[(4) - (11)]).node);
						  AST_prependSibling(block, (yyvsp[(7) - (11)]).node);
						  
          					  
						}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 84 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_FUN, (yyvsp[(1) - (9)]).line);
                				  (yyval).node->stringVal = (yyvsp[(2) - (9)]).cValue ;
          					  AST_addChild((yyval).node, (yyvsp[(4) - (9)]).node);					
					 	  AST* block = AST_new(AST_BLOCK, (yyvsp[(7) - (9)]).line);
						fprintf(stderr, "ENTROUUUUUUUUUUUUU\n");
          					  AST_addChildren(block, (yyvsp[(7) - (9)]).node);
						fprintf(stderr, "SAIUUUUUUUUUUUUU\n");
					  	  AST_addChild((yyval).node, block);
						  AST_prependSibling((yyvsp[(7) - (9)]).node, (yyvsp[(4) - (9)]).node);
						fprintf(stderr, "FUN\n");					  
						//fprintf(stderr, "string    %s\n", $2.cValue);
						fprintf(stderr, "entradas    %d\n", (yyvsp[(7) - (9)]).node);
						//fprintf(stderr, "%d\n", $$.node);
						fprintf(stderr, "params %d\n", (yyvsp[(4) - (9)]).node);  
						fprintf(stderr, "block first  %d\n", block->firstChild) ;
						fprintf(stderr, "block last  %d\n", block->lastChild) ; 						 }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 101 "analisadorSintatico.y"
    { (yyval).node = NULL; //fprintf(stderr, "params2   %d\n", $$.node);
						}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 103 "analisadorSintatico.y"
    { (yyval).node = AST_prependSibling((yyvsp[(2) - (2)]).node, (yyvsp[(1) - (2)]).node);
						//fprintf(stderr, "aaaaaaaa\n"); 
						//fprintf(stderr, "params   %d\n", $$.node);
						}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 108 "analisadorSintatico.y"
    { (yyval).node = NULL; }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 109 "analisadorSintatico.y"
    { (yyval).node = AST_prependSibling((yyvsp[(3) - (3)]).node, (yyvsp[(1) - (3)]).node); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 111 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_PARAM, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, AST_newStringFromToken((yyvsp[(1) - (3)]).cValue, (yyvsp[(1) - (3)]).line));
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 115 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_DECLVAR, (yyvsp[(1) - (5)]).line);
						  AST_addChild((yyval).node, AST_newStringFromToken((yyvsp[(1) - (5)]).cValue, (yyvsp[(1) - (5)]).line));
						  AST_addChild((yyval).node, (yyvsp[(3) - (5)]).node); 
						  //fprintf(stderr, "entradas\n");
						  //fprintf(stderr, "no 5   %d\n", $5.node);
						fprintf(stderr, "DECLVAR   %d\n", (yyval).node);
						  AST_prependSibling((yyvsp[(5) - (5)]).node, (yyval).node); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 123 "analisadorSintatico.y"
    { (yyval).node = AST_prependSibling((yyvsp[(3) - (3)]).node, (yyvsp[(1) - (3)]).node); 
						fprintf(stderr, "$$comando   %d\n", (yyval).node);
						fprintf(stderr, "comando   %d\n", (yyvsp[(1) - (3)]).node);
						fprintf(stderr, "lista_comando   %d\n", (yyvsp[(3) - (3)]).node);}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 127 "analisadorSintatico.y"
    { (yyval).node = NULL; }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 129 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 132 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(3) - (3)]).node; }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 134 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_INT, (yyvsp[(1) - (1)]).line) ;}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 136 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_CHAR, (yyvsp[(1) - (1)]).line) ; }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 137 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_BOOL, (yyvsp[(1) - (1)]).line) ; }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 138 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_STRING, (yyvsp[(1) - (1)]).line) ; }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 140 "analisadorSintatico.y"
    { (yyval).node = NULL; }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 141 "analisadorSintatico.y"
    { (yyval).node = AST_prependSibling((yyvsp[(3) - (3)]).node, (yyvsp[(1) - (3)]).node); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 143 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 144 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 145 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 146 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 147 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; 
						fprintf(stderr, "chamada indo comando   %d\n", (yyval).node);}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 153 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_IF, (yyvsp[(1) - (6)]).line);			
               					  AST_addChild((yyval).node, (yyvsp[(2) - (6)]).node);
             					  AST* block = AST_new(AST_BLOCK, (yyvsp[(4) - (6)]).line);
          					  AST_addChildren(block, (yyvsp[(4) - (6)]).node);
					  	  AST_addChild((yyval).node, block);
						  AST* block_else = AST_new(AST_BLOCK_ELSE, (yyvsp[(5) - (6)]).line);
						  AST_addChildren(block, (yyvsp[(5) - (6)]).node);
					  	  AST_addChild((yyval).node, block_else); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 163 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_ELSEIF, (yyvsp[(1) - (6)]).line);
						  AST_addChild((yyval).node, (yyvsp[(3) - (6)]).node);
						  AST* block = AST_new(AST_BLOCK, (yyvsp[(5) - (6)]).line);
						  AST_addChildren(block, (yyvsp[(5) - (6)]).node);
					  	  AST_addChild((yyval).node, block);
						  AST* block_else = AST_new(AST_BLOCK_ELSE, (yyvsp[(6) - (6)]).line);
						  AST_addChildren(block, (yyvsp[(6) - (6)]).node);
					  	  AST_addChild((yyval).node, block_else); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 172 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_ELSE, (yyvsp[(1) - (3)]).line);
						  AST* block = AST_new(AST_BLOCK, (yyvsp[(3) - (3)]).line);
						  AST_addChildren(block, (yyvsp[(3) - (3)]).node);
					  	  AST_addChild((yyval).node, block); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 177 "analisadorSintatico.y"
    { (yyval).node = NULL; }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 181 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_WHILE, (yyvsp[(1) - (5)]).line);
                				  AST_addChild((yyval).node, (yyvsp[(2) - (5)]).node);
          					  AST* block = AST_new(AST_BLOCK, (yyvsp[(4) - (5)]).line);
						  AST_addChildren(block, (yyvsp[(4) - (5)]).node);
					  	  AST_addChild((yyval).node, block); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 187 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_ATRIB, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, (yyvsp[(1) - (3)]).node);
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 191 "analisadorSintatico.y"
    { (yyval).node = AST_newStringFromToken((yyvsp[(1) - (1)]).cValue, (yyvsp[(1) - (1)]).line); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 192 "analisadorSintatico.y"
    { (yyval).node = AST_prependSibling((yyvsp[(3) - (4)]).node, (yyvsp[(1) - (4)]).node); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 194 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_CALL, (yyvsp[(1) - (4)]).line);
						  AST_addChild((yyval).node, AST_newStringFromToken((yyvsp[(1) - (4)]).cValue, (yyvsp[(1) - (4)]).line));
						  AST_addChild((yyval).node, (yyvsp[(3) - (4)]).node); 
						fprintf(stderr, "chamada   %d\n", (yyval).node);}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 199 "analisadorSintatico.y"
    { (yyval).node = NULL; }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 200 "analisadorSintatico.y"
    { (yyval).node = AST_prependSibling((yyvsp[(2) - (2)]).node, (yyvsp[(1) - (2)]).node); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 202 "analisadorSintatico.y"
    { (yyval).node = NULL; }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 205 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_RET, (yyvsp[(1) - (2)]).line);
						  AST_addChild((yyval).node, (yyvsp[(2) - (2)]).node); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 207 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_RET, (yyvsp[(1) - (1)]).line); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 209 "analisadorSintatico.y"
    {}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 210 "analisadorSintatico.y"
    {}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 212 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 214 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 215 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_OR, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, (yyvsp[(1) - (3)]).node);
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 219 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 220 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_AND, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, (yyvsp[(1) - (3)]).node);
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 224 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 225 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_LESS, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, (yyvsp[(1) - (3)]).node);
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 229 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_GREATER, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, (yyvsp[(1) - (3)]).node);
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 233 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_EQUAL, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, (yyvsp[(1) - (3)]).node);
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 237 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_LESS_EQUAL, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, (yyvsp[(1) - (3)]).node);
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 241 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_GREATER_EQUAL, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, (yyvsp[(1) - (3)]).node);
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 245 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_NOT_EQUAL, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, (yyvsp[(1) - (3)]).node);
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 249 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 250 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_PLUS, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, (yyvsp[(1) - (3)]).node);
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 254 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_MINUS, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, (yyvsp[(1) - (3)]).node);
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 258 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 259 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_TIMES, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, (yyvsp[(1) - (3)]).node);
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 263 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_DIVIDED, (yyvsp[(1) - (3)]).line);
						  AST_addChild((yyval).node, (yyvsp[(1) - (3)]).node);
						  AST_addChild((yyval).node, (yyvsp[(3) - (3)]).node); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 267 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_NOT, (yyvsp[(1) - (2)]).line);
						  AST_addChild((yyval).node, (yyvsp[(2) - (2)]).node); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 270 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_NEG, (yyvsp[(1) - (2)]).line);
						  AST_addChild((yyval).node, (yyvsp[(2) - (2)]).node); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 273 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 275 "analisadorSintatico.y"
    { (yyval).node = AST_newNumFromToken((yyvsp[(1) - (1)]).iValue); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 276 "analisadorSintatico.y"
    { (yyval).node = AST_newStringFromToken((yyvsp[(1) - (1)]).cValue, (yyvsp[(1) - (1)]).line); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 277 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_TRUE, (yyvsp[(1) - (1)]).line) ; }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 278 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_FALSE, (yyvsp[(1) - (1)]).line) ; }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 279 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_NEW, (yyvsp[(1) - (5)]).line);
						  AST_addChild((yyval).node, (yyvsp[(3) - (5)]).node);
						  AST_addChild((yyval).node, (yyvsp[(5) - (5)]).node); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 283 "analisadorSintatico.y"
    { (yyval).node = AST_new(AST_CALL, (yyvsp[(1) - (4)]).line);
						  AST_addChild((yyval).node, AST_newStringFromToken((yyvsp[(1) - (4)]).cValue, (yyvsp[(1) - (4)]).line));
						  AST_addChild((yyval).node, (yyvsp[(3) - (4)]).node); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 286 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(1) - (1)]).node; }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 287 "analisadorSintatico.y"
    { (yyval).node = (yyvsp[(2) - (3)]).node; }
    break;



/* Line 1806 of yacc.c  */
#line 2175 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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
      if (!yypact_value_is_default (yyn))
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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



/* Line 2067 of yacc.c  */
#line 289 "analisadorSintatico.y"

 /*procedimentos auxiliares */

int yywrap (){ }


