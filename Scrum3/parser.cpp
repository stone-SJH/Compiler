/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 6 "parser.y"

	#include <stdio.h>
	#include <stdlib.h>

/* Line 371 of yacc.c  */
#line 73 "parser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EOL = 258,
     FILEEND = 259,
     TYPECHAR = 260,
     TYPEINT = 261,
     TYPEDOUBLE = 262,
     TYPE = 263,
     NAME = 264,
     FUNC = 265,
     VAR = 266,
     AS = 267,
     ARRAY = 268,
     OF = 269,
     IF = 270,
     THEN = 271,
     ELSE = 272,
     ENDIF = 273,
     WHILE = 274,
     ENDWHILE = 275,
     FOR = 276,
     FROM = 277,
     TO = 278,
     STEP = 279,
     ENDFOR = 280,
     FOREACH = 281,
     YYIN = 282,
     ENDFOREACH = 283,
     LET = 284,
     ENDFUNC = 285,
     DEFINE = 286,
     RETURN = 287,
     CLASS = 288,
     EXTENDS = 289,
     ENDCLASS = 290,
     GET = 291,
     CMP = 292,
     UMINUS = 293
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 11 "parser.y"

	struct ast* a;
	struct symlist* sl;
	struct arg* ag;

	char* name;
	int type;
	double d;
	int i;
	char c;

	int fn;


/* Line 387 of yacc.c  */
#line 169 "parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (struct pcdata* pp);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */
/* Line 390 of yacc.c  */
#line 24 "parser.y"

	#include "defination.h"
	#include "lexer.h"
	#define YYLEX_PARAM	 pp->scaninfo

/* Line 390 of yacc.c  */
#line 202 "parser.cpp"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
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
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   359

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNRULES -- Number of states.  */
#define YYNSTATES  204

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    45,    39,     2,
      49,    50,    43,    41,    53,    42,     2,    44,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    52,
       2,    37,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    48,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    38,     2,    46,     2,     2,     2,
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
      35,    36,    40,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    32,    34,    36,    38,
      41,    43,    45,    47,    49,    51,    53,    55,    57,    59,
      61,    67,    78,    84,    89,    96,   101,   109,   113,   120,
     127,   133,   143,   151,   158,   171,   180,   188,   195,   199,
     205,   211,   213,   217,   218,   223,   228,   238,   239,   241,
     245,   249,   253,   257,   261,   265,   269,   272,   276,   280,
     284,   287,   289,   291,   293,   295,   300,   305,   310,   314,
     321,   328
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,     4,    -1,    56,    -1,    57,    -1,    57,
      56,    -1,    60,    -1,    61,    -1,    62,    -1,    65,    -1,
      66,    -1,    68,    -1,    67,    -1,    69,    -1,    70,    -1,
      72,    -1,    63,    -1,    64,    -1,    59,    -1,    59,    58,
      -1,    60,    -1,    61,    -1,    65,    -1,    62,    -1,    66,
      -1,    68,    -1,    67,    -1,    69,    -1,    72,    -1,    71,
      -1,    11,     9,    12,     8,    52,    -1,    11,     9,    12,
      13,    47,     6,    48,    14,     8,    52,    -1,    11,     9,
      12,     9,    52,    -1,    33,     9,    56,    35,    -1,    33,
       9,    34,     9,    56,    35,    -1,     9,    37,    76,    52,
      -1,     9,    47,    76,    48,    37,    76,    52,    -1,     9,
      37,    65,    -1,     9,    47,    76,    48,    37,    65,    -1,
       9,    36,     9,    37,    76,    52,    -1,     9,    36,     9,
      37,    65,    -1,    15,    49,    76,    50,    16,    56,    17,
      56,    18,    -1,    15,    49,    76,    50,    16,    56,    18,
      -1,    19,    49,    76,    50,    56,    20,    -1,    21,    49,
       9,    22,     6,    23,     6,    24,     6,    50,    56,    25,
      -1,    26,    49,     9,    27,     9,    50,    56,    28,    -1,
      29,     9,    49,    73,    50,    58,    30,    -1,    31,     9,
      49,    73,    50,    52,    -1,    32,    76,    52,    -1,    10,
      49,    75,    50,    52,    -1,     9,    49,    75,    50,    52,
      -1,    74,    -1,    74,    53,    73,    -1,    -1,    11,     9,
      12,     8,    -1,    11,     9,    12,     9,    -1,    11,     9,
      12,    13,    47,     6,    48,    14,     8,    -1,    -1,    76,
      -1,    76,    53,    75,    -1,    76,    40,    76,    -1,    76,
      41,    76,    -1,    76,    42,    76,    -1,    76,    43,    76,
      -1,    76,    44,    76,    -1,    76,    45,    76,    -1,    46,
      76,    -1,    76,    39,    76,    -1,    76,    38,    76,    -1,
      49,    76,    50,    -1,    42,    76,    -1,     7,    -1,     5,
      -1,     6,    -1,     9,    -1,     9,    47,    76,    48,    -1,
      10,    49,    75,    50,    -1,     9,    49,    75,    50,    -1,
       9,    36,     9,    -1,     9,    36,    10,    49,    75,    50,
      -1,     9,    36,     9,    49,    75,    50,    -1,     9,    36,
       9,    47,    76,    48,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    65,    65,    66,    68,    69,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    84,    85,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      98,   100,   102,   104,   106,   108,   109,   110,   111,   112,
     113,   115,   116,   118,   120,   122,   124,   125,   127,   129,
     130,   132,   133,   135,   136,   137,   138,   140,   141,   142,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EOL", "FILEEND", "TYPECHAR", "TYPEINT",
  "TYPEDOUBLE", "TYPE", "NAME", "FUNC", "VAR", "AS", "ARRAY", "OF", "IF",
  "THEN", "ELSE", "ENDIF", "WHILE", "ENDWHILE", "FOR", "FROM", "TO",
  "STEP", "ENDFOR", "FOREACH", "YYIN", "ENDFOREACH", "LET", "ENDFUNC",
  "DEFINE", "RETURN", "CLASS", "EXTENDS", "ENDCLASS", "GET", "'='", "'|'",
  "'&'", "CMP", "'+'", "'-'", "'*'", "'/'", "'%'", "'~'", "'['", "']'",
  "'('", "')'", "UMINUS", "';'", "','", "$accept", "prog", "stmtlist",
  "stmt", "infunclist", "infunc", "basedec", "arrdec", "classdec",
  "classdefinestmt", "classsucceed", "asgnstmt", "ifstmt", "whilestmt",
  "forstmt", "foreachstmt", "funcdefinestmt", "returnstmt", "funccallstmt",
  "symlist", "symbol", "explist", "exp", YY_NULL
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
     285,   286,   287,   288,   289,   290,   291,    61,   124,    38,
     292,    43,    45,    42,    47,    37,   126,    91,    93,    40,
      41,   293,    59,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    55,    56,    56,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    58,    58,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      60,    61,    62,    63,    64,    65,    65,    65,    65,    65,
      65,    66,    66,    67,    68,    69,    70,    70,    71,    72,
      72,    73,    73,    74,    74,    74,    74,    75,    75,    75,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,    10,     5,     4,     6,     4,     7,     3,     6,     6,
       5,     9,     7,     6,    12,     8,     7,     6,     3,     5,
       5,     1,     3,     0,     4,     4,     9,     0,     1,     3,
       3,     3,     3,     3,     3,     3,     2,     3,     3,     3,
       2,     1,     1,     1,     1,     4,     4,     4,     3,     6,
       6,     6
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     2,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     4,     6,     7,     8,    16,    17,
       9,    10,    12,    11,    13,    14,    15,     0,     0,     0,
      57,    57,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     5,     0,    72,    73,    71,    74,     0,     0,     0,
       0,    37,     0,    74,     0,     0,    58,     0,     0,     0,
       0,     0,     0,    53,    53,     0,     0,     0,     0,     0,
      57,    57,    70,    66,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,     0,     0,     0,     0,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,     0,    33,    40,     0,    78,     0,     0,     0,     0,
      69,    68,    67,    60,    61,    62,    63,    64,    65,    78,
       0,     0,    50,    59,    49,    30,    32,     0,     0,     0,
       0,     0,     0,     0,    53,     0,     0,    39,     0,    57,
      57,    75,    77,    76,    75,    38,     0,     0,     0,    43,
       0,     0,     0,     0,     0,    18,    20,    21,    23,    22,
      24,    26,    25,    27,    29,    28,    52,    47,    34,     0,
       0,     0,    36,     0,     0,    42,     0,     0,    54,    55,
       0,     0,    46,    19,    81,    80,    79,     0,     0,     0,
      45,     0,    48,     0,    41,     0,     0,    31,     0,     0,
       0,     0,    44,    56
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    12,    13,    14,   154,   155,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,   164,    26,    98,
      99,    55,    56
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -121
static const yytype_int16 yypact[] =
{
      82,  -121,    28,   -37,     9,   -20,    -4,    22,    39,    49,
      89,    90,    96,  -121,   152,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,   100,    21,    27,
      27,    27,    95,    27,    27,   101,   127,    91,    92,   123,
    -121,  -121,   102,  -121,  -121,  -121,    53,    94,    27,    27,
      27,  -121,   172,    36,   271,   103,    78,   105,    -3,   232,
     245,   124,   121,   139,   139,   142,   129,    21,    38,    27,
      27,    27,  -121,  -121,   258,    27,    27,    27,    27,    27,
      27,    27,    27,  -121,    72,    27,   122,   106,    27,   113,
     114,   116,   125,   153,   152,   164,   165,   166,   126,   136,
     130,   152,  -121,  -121,   187,    98,   128,   282,   132,   140,
    -121,   314,   178,   193,    81,    81,  -121,  -121,  -121,   -38,
     293,    21,  -121,  -121,  -121,  -121,  -121,   173,   152,   171,
     170,   144,   183,   177,   139,   145,   167,  -121,    27,    27,
      27,   122,  -121,  -121,  -121,  -121,   202,   151,    87,  -121,
     194,   152,     6,    27,   174,   177,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,   304,
     155,   156,  -121,   234,   152,  -121,   184,   179,  -121,  -121,
     154,   217,  -121,  -121,  -121,  -121,  -121,   241,   233,   244,
    -121,   246,  -121,   201,  -121,   213,   216,  -121,   152,   251,
     242,   260,  -121,  -121
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -121,  -121,   -14,  -121,   111,  -121,  -120,  -117,  -116,  -121,
    -121,   -27,  -113,   -89,   -87,   -76,  -121,  -121,   -71,   -60,
    -121,   -10,   -26
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      41,    51,    52,    54,   100,    90,    91,    59,    60,   138,
      92,   139,    31,   156,   178,   179,   157,   158,    32,   180,
     160,    57,    72,    73,    74,    66,    43,    44,    45,    33,
      46,    47,    43,    44,    45,   156,    53,    47,   157,   158,
     103,   104,   160,   107,   161,    34,   162,   105,   106,   111,
     112,   113,   114,   115,   116,   117,   118,   163,    37,   120,
     108,   109,   165,    48,    27,    28,   161,    49,   162,    48,
      50,    35,    84,    49,   166,    29,    50,    30,   123,   163,
     129,   119,   106,    85,   165,    70,     1,   136,    36,    68,
      28,     2,     3,     4,   145,   146,    40,     5,    38,    39,
      69,     6,    70,     7,   174,   175,   159,    58,     8,    42,
      61,     9,   169,    10,   148,    11,    75,    76,    77,    78,
      79,    80,    81,    82,    80,    81,    82,   181,   159,   170,
     171,    88,     2,     3,     4,    67,    62,   177,     5,    67,
      63,    64,     6,    71,     7,   138,    95,   139,    96,     8,
      97,   101,     9,    87,    10,    89,    11,    65,   122,   121,
     188,     2,     3,     4,   102,   124,   125,     5,   126,   128,
     130,     6,   127,     7,   131,   132,   133,   140,     8,   147,
     135,     9,   142,    10,   200,    11,     2,     3,     4,   134,
     143,   149,     5,   150,   151,   152,     6,   167,     7,   173,
     176,   191,   168,     8,   182,   185,   186,   190,   189,   153,
      75,    76,    77,    78,    79,    80,    81,    82,    77,    78,
      79,    80,    81,    82,    83,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    78,    79,    80,    81,    82,   137,
      75,    76,    77,    78,    79,    80,    81,    82,   187,   193,
     195,   194,   196,   197,   172,    75,    76,    77,    78,    79,
      80,    81,    82,   198,   199,   201,   183,   202,   203,   192,
      75,    76,    77,    78,    79,    80,    81,    82,     0,     0,
       0,     0,    93,    75,    76,    77,    78,    79,    80,    81,
      82,     0,     0,     0,     0,    94,    75,    76,    77,    78,
      79,    80,    81,    82,     0,     0,     0,     0,   110,    75,
      76,    77,    78,    79,    80,    81,    82,     0,     0,    86,
      75,    76,    77,    78,    79,    80,    81,    82,     0,     0,
     141,    75,    76,    77,    78,    79,    80,    81,    82,     0,
       0,   144,    75,    76,    77,    78,    79,    80,    81,    82,
       0,     0,   184,    76,    77,    78,    79,    80,    81,    82
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-121)))

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

static const yytype_int16 yycheck[] =
{
      14,    28,    28,    29,    64,     8,     9,    33,    34,    47,
      13,    49,    49,   133,     8,     9,   133,   133,     9,    13,
     133,    31,    48,    49,    50,    39,     5,     6,     7,    49,
       9,    10,     5,     6,     7,   155,     9,    10,   155,   155,
      67,    67,   155,    69,   133,    49,   133,     9,    10,    75,
      76,    77,    78,    79,    80,    81,    82,   133,     9,    85,
      70,    71,   133,    42,    36,    37,   155,    46,   155,    42,
      49,    49,    36,    46,   134,    47,    49,    49,    88,   155,
      94,     9,    10,    47,   155,    49,     4,   101,    49,    36,
      37,     9,    10,    11,   121,   121,     0,    15,     9,     9,
      47,    19,    49,    21,    17,    18,   133,    12,    26,     9,
       9,    29,   138,    31,   128,    33,    38,    39,    40,    41,
      42,    43,    44,    45,    43,    44,    45,   153,   155,   139,
     140,    53,     9,    10,    11,    37,     9,   151,    15,    37,
      49,    49,    19,    49,    21,    47,    22,    49,    27,    26,
      11,     9,    29,    50,    31,    50,    33,    34,    52,    37,
     174,     9,    10,    11,    35,    52,    52,    15,    52,    16,
       6,    19,    47,    21,     9,     9,    50,    49,    26,     6,
      50,    29,    50,    31,   198,    33,     9,    10,    11,    53,
      50,    20,    15,    23,    50,    12,    19,    52,    21,    48,
       6,    47,    35,    26,    30,    50,    50,    28,    24,    32,
      38,    39,    40,    41,    42,    43,    44,    45,    40,    41,
      42,    43,    44,    45,    52,    38,    39,    40,    41,    42,
      43,    44,    45,    40,    41,    42,    43,    44,    45,    52,
      38,    39,    40,    41,    42,    43,    44,    45,    14,     8,
       6,    18,     6,    52,    52,    38,    39,    40,    41,    42,
      43,    44,    45,    50,    48,    14,   155,    25,     8,    52,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,    50,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    50,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    50,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    48,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      48,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    48,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    48,    39,    40,    41,    42,    43,    44,    45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     9,    10,    11,    15,    19,    21,    26,    29,
      31,    33,    55,    56,    57,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    72,    36,    37,    47,
      49,    49,     9,    49,    49,    49,    49,     9,     9,     9,
       0,    56,     9,     5,     6,     7,     9,    10,    42,    46,
      49,    65,    76,     9,    76,    75,    76,    75,    12,    76,
      76,     9,     9,    49,    49,    34,    56,    37,    36,    47,
      49,    49,    76,    76,    76,    38,    39,    40,    41,    42,
      43,    44,    45,    52,    36,    47,    48,    50,    53,    50,
       8,     9,    13,    50,    50,    22,    27,    11,    73,    74,
      73,     9,    35,    65,    76,     9,    10,    76,    75,    75,
      50,    76,    76,    76,    76,    76,    76,    76,    76,     9,
      76,    37,    52,    75,    52,    52,    52,    47,    16,    56,
       6,     9,     9,    50,    53,    50,    56,    52,    47,    49,
      49,    48,    50,    50,    48,    65,    76,     6,    56,    20,
      23,    50,    12,    32,    58,    59,    60,    61,    62,    65,
      66,    67,    68,    69,    71,    72,    73,    52,    35,    76,
      75,    75,    52,    48,    17,    18,     6,    56,     8,     9,
      13,    76,    30,    58,    48,    50,    50,    14,    56,    24,
      28,    47,    52,     8,    18,     6,     6,    52,    50,    48,
      56,    14,    25,     8
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

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (pp, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
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
		  Type, Value, pp); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct pcdata* pp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, pp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    struct pcdata* pp;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (pp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct pcdata* pp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, pp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    struct pcdata* pp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, pp);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, struct pcdata* pp)
#else
static void
yy_reduce_print (yyvsp, yyrule, pp)
    YYSTYPE *yyvsp;
    int yyrule;
    struct pcdata* pp;
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
		       		       , pp);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, pp); \
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, struct pcdata* pp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, pp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    struct pcdata* pp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (pp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




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
yyparse (struct pcdata* pp)
#else
int
yyparse (pp)
    struct pcdata* pp;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1792 of yacc.c  */
#line 65 "parser.y"
    { pp->ast=NULL; YYACCEPT; }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 66 "parser.y"
    { pp->ast=(yyvsp[(1) - (1)].a); YYACCEPT; }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 68 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 69 "parser.y"
    { (yyval.a)=newast(pp,'L',(yyvsp[(1) - (2)].a),(yyvsp[(2) - (2)].a)); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 71 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 72 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 73 "parser.y"
    {(yyval.a)=(yyvsp[(1) - (1)].a);}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 74 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 75 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 76 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 77 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 78 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 79 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 80 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 81 "parser.y"
    {(yyval.a)=(yyvsp[(1) - (1)].a);}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 82 "parser.y"
    {(yyval.a)=(yyvsp[(1) - (1)].a);}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 84 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 85 "parser.y"
    { (yyval.a)=newast(pp,'L',(yyvsp[(1) - (2)].a),(yyvsp[(2) - (2)].a)); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 87 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 88 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 89 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 90 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 91 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 92 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 93 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 94 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 95 "parser.y"
    { (yyval.a)=(yyvsp[(1) - (1)].a); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 96 "parser.y"
    {(yyval.a)=(yyvsp[(1) - (1)].a);}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 98 "parser.y"
    { (yyval.a)=newvar(pp,(yyvsp[(2) - (5)].name),(yyvsp[(4) - (5)].type)); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 100 "parser.y"
    {(yyval.a)=newarr(pp,(yyvsp[(2) - (10)].name),(yyvsp[(9) - (10)].type),(yyvsp[(6) - (10)].i)); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 102 "parser.y"
    {(yyval.a)=newclass(pp,(yyvsp[(2) - (5)].name),(yyvsp[(4) - (5)].name)); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 104 "parser.y"
    {(yyval.a)=newclassdef(pp,(yyvsp[(2) - (4)].name),NULL,(yyvsp[(3) - (4)].a));}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 106 "parser.y"
    { (yyval.a)=newclassdef(pp,(yyvsp[(2) - (6)].name),(yyvsp[(4) - (6)].name),(yyvsp[(5) - (6)].a));}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 108 "parser.y"
    {  (yyval.a)=newasgn(pp,NULL,(yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].a),NULL); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 109 "parser.y"
    { (yyval.a)=newasgn(pp,NULL,(yyvsp[(1) - (7)].name),(yyvsp[(6) - (7)].a),(yyvsp[(3) - (7)].a)); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 110 "parser.y"
    {  (yyval.a)=newasgn(pp,NULL,(yyvsp[(1) - (3)].name),(yyvsp[(3) - (3)].a),NULL); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 111 "parser.y"
    { (yyval.a)=newasgn(pp,NULL,(yyvsp[(1) - (6)].name),(yyvsp[(6) - (6)].a),(yyvsp[(3) - (6)].a)); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 112 "parser.y"
    { (yyval.a)=newasgn(pp,(yyvsp[(1) - (6)].name),(yyvsp[(3) - (6)].name),(yyvsp[(5) - (6)].a),NULL);}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 113 "parser.y"
    { (yyval.a)=newasgn(pp,(yyvsp[(1) - (5)].name),(yyvsp[(3) - (5)].name),(yyvsp[(5) - (5)].a),NULL);}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 115 "parser.y"
    { (yyval.a)=newflow(pp,'I',(yyvsp[(3) - (9)].a),(yyvsp[(6) - (9)].a),(yyvsp[(8) - (9)].a)); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 116 "parser.y"
    {(yyval.a)=newflow(pp,'I',(yyvsp[(3) - (7)].a),(yyvsp[(6) - (7)].a),NULL);}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 118 "parser.y"
    { (yyval.a)=newflow(pp,'W',(yyvsp[(3) - (6)].a),(yyvsp[(5) - (6)].a),NULL); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 120 "parser.y"
    { (yyval.a)=newfor(pp,(yyvsp[(3) - (12)].name),(yyvsp[(5) - (12)].i),(yyvsp[(7) - (12)].i),(yyvsp[(9) - (12)].i),(yyvsp[(11) - (12)].a)); }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 122 "parser.y"
    { (yyval.a)=newforeach(pp,(yyvsp[(3) - (8)].name),(yyvsp[(5) - (8)].name),(yyvsp[(7) - (8)].a)); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 124 "parser.y"
    { (yyval.a)=dodef(pp,(yyvsp[(2) - (7)].name),(yyvsp[(4) - (7)].sl),(yyvsp[(6) - (7)].a)); }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 125 "parser.y"
    { (yyval.a)=dodef(pp,(yyvsp[(2) - (6)].name),(yyvsp[(4) - (6)].sl),NULL); }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 127 "parser.y"
    { (yyval.a)=newast(pp,'R',(yyvsp[(2) - (3)].a),NULL);}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 129 "parser.y"
    {(yyval.a)=newfunc(pp,(yyvsp[(1) - (5)].fn),(yyvsp[(3) - (5)].a)); }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 130 "parser.y"
    { (yyval.a)=newcall(pp,(yyvsp[(1) - (5)].name),(yyvsp[(3) - (5)].a)); }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 132 "parser.y"
    {(yyval.sl)=newsymlist(pp,(yyvsp[(1) - (1)].ag),NULL);}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 133 "parser.y"
    { (yyval.sl)=newsymlist(pp,(yyvsp[(1) - (3)].ag),(yyvsp[(3) - (3)].sl)); }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 135 "parser.y"
    { (yyval.ag)=NULL; }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 136 "parser.y"
    { (yyval.ag)=newarg(pp,(yyvsp[(2) - (4)].name),(yyvsp[(4) - (4)].type),NULL,-1); }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 137 "parser.y"
    {(yyval.ag)=newarg(pp,(yyvsp[(2) - (4)].name),-1,(yyvsp[(4) - (4)].name),-1); }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 138 "parser.y"
    { (yyval.ag)=newarg(pp,(yyvsp[(2) - (9)].name),(yyvsp[(9) - (9)].type),NULL,(yyvsp[(6) - (9)].i)); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 142 "parser.y"
    { (yyval.a)=newast(pp,'L',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a)); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 144 "parser.y"
    { (yyval.a)=newcmp(pp,(yyvsp[(2) - (3)].fn),(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a)); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 145 "parser.y"
    { (yyval.a)=newast(pp,'+',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a)); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 146 "parser.y"
    { (yyval.a)=newast(pp,'-',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a)); }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 147 "parser.y"
    { (yyval.a)=newast(pp,'*',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a)); }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 148 "parser.y"
    { (yyval.a)=newast(pp,'/',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a)); }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 149 "parser.y"
    { (yyval.a)=newast(pp,'%',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a)); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 150 "parser.y"
    { (yyval.a)=newast(pp,'~',(yyvsp[(2) - (2)].a),NULL);}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 151 "parser.y"
    { (yyval.a)=newast(pp,'&',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a));}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 152 "parser.y"
    { (yyval.a)=newast(pp,'|',(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a)); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 153 "parser.y"
    { (yyval.a)=(yyvsp[(2) - (3)].a); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 154 "parser.y"
    { (yyval.a)=newast(pp,'M',(yyvsp[(2) - (2)].a),NULL); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 155 "parser.y"
    { (yyval.a)=newdoub(pp,(yyvsp[(1) - (1)].d)); }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 156 "parser.y"
    { (yyval.a)=newchar(pp,(yyvsp[(1) - (1)].c)); }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 157 "parser.y"
    { (yyval.a)=newint(pp,(yyvsp[(1) - (1)].i)); }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 158 "parser.y"
    {  (yyval.a)=newref(pp,(yyvsp[(1) - (1)].name),NULL); }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 159 "parser.y"
    { (yyval.a)=newref(pp,(yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].a)); }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 160 "parser.y"
    {(yyval.a)=newfunc(pp,(yyvsp[(1) - (4)].fn),(yyvsp[(3) - (4)].a)); }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 161 "parser.y"
    { (yyval.a)=newcall(pp,(yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].a)); }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 162 "parser.y"
    {(yyval.a)=newcsget(pp,(yyvsp[(1) - (3)].name),(yyvsp[(3) - (3)].name),-1,NULL,NULL);}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 163 "parser.y"
    { (yyval.a)=newcsget(pp,(yyvsp[(1) - (6)].name),NULL,(yyvsp[(3) - (6)].fn),(yyvsp[(5) - (6)].a),NULL);}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 164 "parser.y"
    { (yyval.a)=newcsget(pp,(yyvsp[(1) - (6)].name),(yyvsp[(3) - (6)].name),-1,(yyvsp[(5) - (6)].a),NULL); }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 165 "parser.y"
    { (yyval.a)=newcsget(pp,(yyvsp[(1) - (6)].name),(yyvsp[(3) - (6)].name),-1,NULL,(yyvsp[(5) - (6)].a)); }
    break;


/* Line 1792 of yacc.c  */
#line 2081 "parser.cpp"
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
      yyerror (pp, YY_("syntax error"));
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
        yyerror (pp, yymsgp);
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
		      yytoken, &yylval, pp);
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
		  yystos[yystate], yyvsp, pp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (pp, YY_("memory exhausted"));
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
                  yytoken, &yylval, pp);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, pp);
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


/* Line 2055 of yacc.c  */
#line 167 "parser.y"
