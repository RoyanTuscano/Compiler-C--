/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 13 "parser.y" /* yacc.c:339  */

#include "global.h"
#include "error.h"
#include "syntax-tree.h"
#include "symbol-table.h"

extern int yylex();
extern void yyerror();
// extern void printSyntaxTree(tnode *t, int n, int depth);
 extern void enter_function(tnode *t, char *fun_name);

  /*
   * struct treenode *currfnbodyTree is set to point to
   * the syntax tree for the body of the current function
   * at the end of each function.  
   * NOTE: the syntax tree MUST be used before CleanupFnInfo()
   * is called at the end of the function.  After that the
   * symbol table entries for the local variables of the
   * function will go away, leaving dangling pointers from
   * the syntax tree.
   */
struct treenode *currfnbodyTree = NULL;

extern char *id_name, *yytext;
 extern int ival;
extern int linenum;
char *fnName;
symtabnode *stptr, *currFun;
int CurrType, EltType, fnRetType;
int CurrScope = Global;
llistptr lptr;
bool is_extern;
int errstate = 0;

#line 101 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INTCON = 259,
    CHARCON = 260,
    STRINGCON = 261,
    CHAR = 262,
    INT = 263,
    VOID = 264,
    EXTERN = 265,
    IF = 266,
    ELSE = 267,
    WHILE = 268,
    FOR = 269,
    RETURN = 270,
    AND = 271,
    OR = 272,
    EQ = 273,
    NEQ = 274,
    LE = 275,
    GE = 276
  };
#endif
/* Tokens.  */
#define ID 258
#define INTCON 259
#define CHARCON 260
#define STRINGCON 261
#define CHAR 262
#define INT 263
#define VOID 264
#define EXTERN 265
#define IF 266
#define ELSE 267
#define WHILE 268
#define FOR 269
#define RETURN 270
#define AND 271
#define OR 272
#define EQ 273
#define NEQ 274
#define LE 275
#define GE 276

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 48 "parser.y" /* yacc.c:355  */

  tnptr tptr;
  llistptr idlistptr;
  char *chptr;
  int nval;

#line 190 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 207 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   294

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  181

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,     2,     2,     2,     2,     2,
      31,    32,    28,    26,    30,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    33,
      22,    24,    23,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,    35,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    81,    81,    83,    85,    88,    87,   107,   110,   112,
     121,   121,   122,   126,   138,   139,   143,   144,   148,   149,
     154,   155,   156,   160,   161,   165,   169,   169,   170,   170,
     171,   175,   186,   200,   204,   205,   209,   215,   221,   227,
     251,   252,   253,   254,   255,   263,   264,   264,   268,   269,
     269,   273,   277,   278,   282,   283,   287,   288,   292,   293,
     297,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   348,   372,   394,   405,   431,   457,   468,
     478,   505,   520,   521,   524
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTCON", "CHARCON", "STRINGCON",
  "CHAR", "INT", "VOID", "EXTERN", "IF", "ELSE", "WHILE", "FOR", "RETURN",
  "AND", "OR", "EQ", "NEQ", "LE", "GE", "'<'", "'>'", "'='", "'!'", "'+'",
  "'-'", "'*'", "'/'", "','", "'('", "')'", "';'", "'{'", "'}'", "'['",
  "']'", "$accept", "prog", "$@1", "Extern", "SetFnInfo", "fprotRest",
  "$@2", "fprototype", "parm_types", "nonempty_parm_type_list",
  "parm_type_decl", "type", "var_decls", "var_decl", "id_list", "$@3",
  "$@4", "id_decl", "ArraySize", "stmt_list", "stmt", "semicolon", "$@5",
  "comma", "$@6", "compound_stmt", "optional_else", "optional_assgt",
  "optional_expr", "optional_boolexp", "assignment", "boolexp", "expr",
  "fun_call", "proc_call", "variable", "expr_list", "Ident", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    60,    62,    61,    33,    43,    45,    42,    47,
      44,    40,    41,    59,   123,   125,    91,    93
};
# endif

#define YYPACT_NINF -108

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-108)))

#define YYTABLE_NINF -94

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -108,   266,  -108,  -108,  -108,  -108,  -108,   200,   137,    24,
      16,  -108,    57,  -108,     0,    22,  -108,  -108,    70,  -108,
    -108,  -108,    84,  -108,    24,  -108,    24,   208,  -108,    63,
     208,  -108,    96,  -108,   102,   101,    25,  -108,    24,  -108,
     117,    73,   200,   119,    92,  -108,  -108,  -108,  -108,  -108,
      91,  -108,  -108,    24,  -108,   128,  -108,   129,  -108,   133,
     134,   136,    93,  -108,     9,   137,   126,   135,     9,  -108,
     139,   139,   145,     1,    92,   208,   228,   228,    24,  -108,
    -108,  -108,    93,   193,   139,   265,  -108,  -108,    30,   138,
      25,  -108,  -108,  -108,  -108,  -108,   174,  -108,    93,   147,
     199,  -108,   149,   228,   187,    33,   242,    52,   139,  -108,
     150,  -108,   155,   258,  -108,    93,    93,    93,    93,   179,
    -108,  -108,   265,   157,  -108,   251,   163,   164,    82,  -108,
    -108,    69,   217,   228,   228,   143,    93,    93,    93,    93,
      93,    93,   143,   228,  -108,  -108,    11,    11,  -108,  -108,
     181,  -108,   189,  -108,    93,  -108,  -108,  -108,  -108,  -108,
    -108,   207,   265,   265,   265,   265,   265,   265,  -108,   139,
      62,  -108,  -108,  -108,   143,  -108,    24,  -108,   190,   143,
    -108
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       7,     0,     1,    21,    20,    22,     8,     0,     0,     0,
      49,    94,    49,    30,    31,     0,    48,    28,     0,     2,
      26,     9,     0,     9,     0,    50,     0,     0,    33,     0,
       0,    29,    31,    27,    14,     0,    15,    17,     0,    32,
       0,    49,     0,    18,    49,    12,     5,     3,    10,    16,
       0,     4,    24,     0,    19,     0,     9,     0,    44,     0,
       0,     0,    57,    43,     0,     0,     0,     0,     0,    42,
      46,    46,     0,    89,    49,     0,     0,     0,    55,    80,
      81,    82,     0,     0,    46,    56,    76,    77,    89,     0,
      25,    23,     6,    34,    45,    40,     0,    41,     0,     0,
       0,    11,     0,     0,     0,     0,     0,     0,    46,    54,
      89,    71,     0,     0,    39,     0,     0,     0,     0,     0,
      51,    47,    60,     0,    86,    49,     0,     0,     0,    13,
      67,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,    79,    78,    72,    73,    74,    75,
       0,    83,     0,    88,     0,    87,    91,    90,    70,    68,
      69,    53,    61,    62,    63,    64,    65,    66,    37,    46,
      58,    85,    84,    92,     0,    36,    55,    52,     0,     0,
      38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -108,  -108,  -108,  -108,    -4,   -23,  -108,  -108,   -21,  -108,
     183,     7,  -108,  -108,   158,  -108,  -108,   121,  -108,    13,
    -107,   -67,  -108,    -7,  -108,  -108,  -108,    51,  -108,  -108,
     -72,   -70,   -24,  -108,  -108,   -53,  -106,    -8
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    52,     7,    27,    47,    53,    56,    35,    36,
      37,    38,    55,    66,    12,    26,    24,    13,    29,    67,
      68,    95,    96,    48,    18,    69,   175,   108,    84,   169,
      70,   105,   106,    86,    71,    87,   126,    88
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,    15,    72,    17,    97,    20,   109,   107,     8,    40,
      58,    72,    11,   152,     9,    72,    32,   114,    32,    30,
      59,    51,    60,    61,    62,    72,   -49,    11,   161,    42,
      43,    21,    99,   130,   131,   168,    22,   100,    85,   117,
     118,   143,    63,    64,   -35,    57,    16,    73,   173,   133,
     134,   101,    74,    23,   102,    16,    73,    32,   111,   113,
      73,   119,    65,   159,   160,   135,   100,   177,   133,   134,
     110,    25,   180,   170,   122,   125,   128,    89,   133,   134,
     132,    93,    72,    20,   142,   133,   134,    16,    28,    72,
      19,   146,   147,   148,   149,   125,    11,    79,    80,    81,
      39,   158,   176,    16,   109,   -22,    45,    46,   115,   116,
     117,   118,   162,   163,   164,   165,   166,   167,   154,   157,
      82,    72,    16,    72,    83,    45,    72,    73,    54,    58,
     125,    11,    22,    41,    73,     3,     4,     5,    10,    59,
      11,    60,    61,    62,    58,    31,    11,    33,   123,    44,
      11,    79,    80,    81,    59,    50,    60,    61,    62,    91,
      75,    63,    64,   -35,    76,    77,    73,    78,   110,    98,
      92,    73,    94,   120,    82,   121,    63,    64,    83,   124,
     150,   129,    11,    79,    80,    81,   100,   144,   112,   153,
      11,    79,    80,    81,   112,   155,    11,    79,    80,    81,
     127,   156,    11,    79,    80,    81,    82,     3,     4,     5,
      83,   151,   103,   171,    82,     3,     4,    34,   104,   174,
      82,   172,   179,    90,    83,    49,    82,   178,     0,     0,
      83,    11,    79,    80,    81,   136,   137,   138,   139,   140,
     141,     0,     0,   115,   116,   117,   118,     0,     0,   145,
       0,     0,     0,   103,     0,    82,     0,     0,     0,   104,
     136,   137,   138,   139,   140,   141,     2,     0,   115,   116,
     117,   118,     0,     3,     4,     5,     6,   115,   116,   117,
     118,    16,     0,   -93,   115,   116,   117,   118,     0,     0,
     145,   115,   116,   117,   118
};

static const yytype_int16 yycheck[] =
{
       8,     9,    55,    10,    71,    12,    78,    77,     1,    30,
       1,    64,     3,   119,     7,    68,    24,    84,    26,    23,
      11,    44,    13,    14,    15,    78,     1,     3,   135,    36,
      38,    31,    31,   103,   104,   142,    36,    36,    62,    28,
      29,   108,    33,    34,    35,    53,    30,    55,   154,    16,
      17,    74,    56,    31,    75,    30,    64,    65,    82,    83,
      68,    31,    55,   133,   134,    32,    36,   174,    16,    17,
      78,     1,   179,   143,    98,    99,   100,    64,    16,    17,
     104,    68,   135,    90,    32,    16,    17,    30,     4,   142,
      33,   115,   116,   117,   118,   119,     3,     4,     5,     6,
      37,    32,   169,    30,   176,     3,    33,    34,    26,    27,
      28,    29,   136,   137,   138,   139,   140,   141,   125,    37,
      27,   174,    30,   176,    31,    33,   179,   135,    37,     1,
     154,     3,    36,    32,   142,     7,     8,     9,     1,    11,
       3,    13,    14,    15,     1,    24,     3,    26,     1,    32,
       3,     4,     5,     6,    11,    36,    13,    14,    15,    33,
      31,    33,    34,    35,    31,    31,   174,    31,   176,    24,
      35,   179,    33,    35,    27,     1,    33,    34,    31,    32,
       1,    32,     3,     4,     5,     6,    36,    32,     1,    32,
       3,     4,     5,     6,     1,    32,     3,     4,     5,     6,
       1,    37,     3,     4,     5,     6,    27,     7,     8,     9,
      31,    32,    25,    32,    27,     7,     8,     9,    31,    12,
      27,    32,    32,    65,    31,    42,    27,   176,    -1,    -1,
      31,     3,     4,     5,     6,    18,    19,    20,    21,    22,
      23,    -1,    -1,    26,    27,    28,    29,    -1,    -1,    32,
      -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,
      18,    19,    20,    21,    22,    23,     0,    -1,    26,    27,
      28,    29,    -1,     7,     8,     9,    10,    26,    27,    28,
      29,    30,    -1,    32,    26,    27,    28,    29,    -1,    -1,
      32,    26,    27,    28,    29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    39,     0,     7,     8,     9,    10,    41,    49,    49,
       1,     3,    52,    55,    75,    75,    30,    61,    62,    33,
      61,    31,    36,    31,    54,     1,    53,    42,     4,    56,
      42,    55,    75,    55,     9,    46,    47,    48,    49,    37,
      46,    32,    61,    75,    32,    33,    34,    43,    61,    48,
      36,    43,    40,    44,    37,    50,    45,    75,     1,    11,
      13,    14,    15,    33,    34,    49,    51,    57,    58,    63,
      68,    72,    73,    75,    42,    31,    31,    31,    31,     4,
       5,     6,    27,    31,    66,    70,    71,    73,    75,    57,
      52,    33,    35,    57,    33,    59,    60,    59,    24,    31,
      36,    43,    46,    25,    31,    69,    70,    69,    65,    68,
      75,    70,     1,    70,    59,    26,    27,    28,    29,    31,
      35,     1,    70,     1,    32,    70,    74,     1,    70,    32,
      69,    69,    70,    16,    17,    32,    18,    19,    20,    21,
      22,    23,    32,    59,    32,    32,    70,    70,    70,    70,
       1,    32,    74,    32,    61,    32,    37,    37,    32,    69,
      69,    58,    70,    70,    70,    70,    70,    70,    58,    67,
      69,    32,    32,    74,    12,    64,    59,    58,    65,    32,
      58
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    39,    39,    40,    39,    39,    41,    42,
      44,    43,    43,    45,    46,    46,    47,    47,    48,    48,
      49,    49,    49,    50,    50,    51,    53,    52,    54,    52,
      52,    55,    55,    56,    57,    57,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    59,    60,    59,    61,    62,
      61,    63,    64,    64,    65,    65,    66,    66,    67,    67,
      68,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    71,    71,    71,    72,    72,    72,    73,
      73,    73,    74,    74,    75
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     8,     9,     0,    12,     0,     1,     0,
       0,     5,     1,     4,     1,     1,     3,     1,     2,     4,
       1,     1,     1,     3,     0,     2,     0,     4,     0,     4,
       1,     1,     4,     1,     2,     0,     6,     5,     9,     3,
       2,     2,     1,     1,     1,     1,     0,     2,     1,     0,
       2,     3,     2,     0,     1,     0,     1,     0,     1,     0,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     3,
       3,     2,     3,     3,     3,     3,     1,     1,     3,     3,
       1,     1,     1,     3,     4,     4,     3,     4,     4,     1,
       4,     4,     3,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:
#line 88 "parser.y" /* yacc.c:1646  */
    { currFun = SymTabRecordFunInfo(false);}
#line 1431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 90 "parser.y" /* yacc.c:1646  */
    { 
      currfnbodyTree = AppendReturn((yyvsp[-1].tptr));
      /*
       * At this point, currfnbodyTree points to the syntax tree
       * for the body of the current function.  This can then
       * be traversed for code generation etc.
       */
      
//#ifdef DEBUG
      //printf("@@FUN: %s\n", $3);
      //printf("@@BODY:\n");
       enter_function(currfnbodyTree,(yyvsp[-9].chptr));
     // printSyntaxTree(currfnbodyTree, 4, 0);
     // printf("-----\n");
//#endif
      CleanupFnInfo(); 
    }
#line 1453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 110 "parser.y" /* yacc.c:1646  */
    { is_extern = true; }
#line 1459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 112 "parser.y" /* yacc.c:1646  */
    { 
	CurrScope = Local; 
	fnRetType = CurrType;
	fnName = id_name;
	lptr = NULL;
  }
#line 1470 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 121 "parser.y" /* yacc.c:1646  */
    { SymTabRecordFunInfo(true); }
#line 1476 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 122 "parser.y" /* yacc.c:1646  */
    { SymTabRecordFunInfo(true); CleanupFnInfo(); }
#line 1482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 126 "parser.y" /* yacc.c:1646  */
    { 
    stptr = SymTabLookupAll((yyvsp[-3].chptr));
    if (stptr != NULL) {
      errmsg("%s multiply declared", (yyvsp[-3].chptr));
    }
    else {
      CurrScope = Local;
    }
 }
#line 1496 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 138 "parser.y" /* yacc.c:1646  */
    { (yyval.idlistptr) = NULL; }
#line 1502 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 139 "parser.y" /* yacc.c:1646  */
    { (yyval.idlistptr) = (yyvsp[0].idlistptr); }
#line 1508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 143 "parser.y" /* yacc.c:1646  */
    { lptr = Attach((yyvsp[-2].idlistptr), (yyvsp[0].idlistptr)); (yyval.idlistptr) = lptr; }
#line 1514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 144 "parser.y" /* yacc.c:1646  */
    { (yyval.idlistptr) = (yyvsp[0].idlistptr); }
#line 1520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 148 "parser.y" /* yacc.c:1646  */
    { lptr = NewListNode((yyvsp[0].chptr), (yyvsp[-1].nval), false); (yyval.idlistptr) = lptr; }
#line 1526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 149 "parser.y" /* yacc.c:1646  */
    { lptr = NewListNode((yyvsp[-2].chptr), (yyvsp[-3].nval), true); (yyval.idlistptr) = lptr; }
#line 1532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 154 "parser.y" /* yacc.c:1646  */
    { (yyval.nval) = CurrType = t_Int; }
#line 1538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 155 "parser.y" /* yacc.c:1646  */
    { (yyval.nval) = CurrType = t_Char; }
#line 1544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 156 "parser.y" /* yacc.c:1646  */
    { (yyval.nval) = CurrType = t_None; }
#line 1550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 169 "parser.y" /* yacc.c:1646  */
    {yyerrok;}
#line 1556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 170 "parser.y" /* yacc.c:1646  */
    {yyerrok;}
#line 1562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 175 "parser.y" /* yacc.c:1646  */
    { 
    if (CurrType == t_None) {
      errmsg("Illegal type [void] for variable %s", id_name);
    }
    else {
      stptr = SymTabInsert(id_name, CurrScope); 
      stptr->type = CurrType;
      stptr->formal = stptr->is_extern = false;
      stptr->elt_type = t_None;
    }
  }
#line 1578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 186 "parser.y" /* yacc.c:1646  */
    { 
    if (CurrType == t_None) {
      errmsg("Illegal type [void] for variable %s", id_name);
    }
    else {
      stptr = SymTabInsert(id_name, CurrScope);
      stptr->type = t_Array;
      stptr->formal = false;
      stptr->elt_type = CurrType;
      stptr->num_elts = (yyvsp[-1].nval);
    }
  }
#line 1595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 200 "parser.y" /* yacc.c:1646  */
    { (yyval.nval) = atoi(yytext); }
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 204 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = mkListNode((yyvsp[-1].tptr), (yyvsp[0].tptr)); }
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 205 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = NULL; }
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 209 "parser.y" /* yacc.c:1646  */
    {
      if ((yyvsp[-3].tptr)->etype != t_Bool && (yyvsp[-3].tptr)->etype != t_Error) {
        errmsg("conditional does not have Boolean type");
      }
      (yyval.tptr) = mkSTNode(If, t_None, (yyvsp[-3].tptr), (yyvsp[-1].tptr), (yyvsp[0].tptr), NULL);
    }
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 215 "parser.y" /* yacc.c:1646  */
    {
      if ((yyvsp[-2].tptr)->etype != t_Bool && (yyvsp[-2].tptr)->etype != t_Error) {
        errmsg("conditional does not have Boolean type");
      }
      (yyval.tptr) = mkSTNode(While, t_None, (yyvsp[-2].tptr), (yyvsp[0].tptr), NULL, NULL);
    }
#line 1635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 221 "parser.y" /* yacc.c:1646  */
    {
      if ((yyvsp[-4].tptr) != NULL && (yyvsp[-4].tptr)->etype != t_Bool && (yyvsp[-4].tptr)->etype != t_Error) {
        errmsg("conditional does not have Boolean type");
      }
      (yyval.tptr) = mkSTNode(For, t_None, (yyvsp[-6].tptr), (yyvsp[-4].tptr), (yyvsp[-2].tptr), (yyvsp[0].tptr));
    }
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 227 "parser.y" /* yacc.c:1646  */
    {
      if (currFun->ret_type != t_None) {
	if ((yyvsp[-1].tptr) == NULL) {
	  errmsg("return with no return value in non-void function");
          (yyval.tptr) = mkErrorNode();
	}
	else if ( !((yyvsp[-1].tptr)->etype == t_Int || (yyvsp[-1].tptr)->etype == t_Char || (yyvsp[-1].tptr)->etype == t_Error) ) {
	  errmsg("illegal return type");
          (yyval.tptr) = mkErrorNode();
	}
	else {
	  (yyval.tptr) = mkSTNode(Return, (yyvsp[-1].tptr)->etype, (yyvsp[-1].tptr), NULL, NULL, NULL);
	}
      }
      else {
	if ((yyvsp[-1].tptr) != NULL) {    /* there is a return expression  */
	  errmsg("non-void return expression in function with no return value");
          (yyval.tptr) = mkErrorNode();
	}
	else {
	  (yyval.tptr) = mkSTNode(Return, t_None, NULL, NULL, NULL, NULL);
	}
      }
    }
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 251 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = (yyvsp[-1].tptr); }
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 252 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = (yyvsp[-1].tptr); }
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 253 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = (yyvsp[0].tptr); }
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 254 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = NULL; }
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 255 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = mkErrorNode(); }
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 264 "parser.y" /* yacc.c:1646  */
    {errstate = NOSEMICOLON;}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 269 "parser.y" /* yacc.c:1646  */
    {errstate = NOCOMMA;}
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 273 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = (yyvsp[-1].tptr); }
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 277 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = (yyvsp[0].tptr); }
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 278 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = NULL; }
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 282 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = (yyvsp[0].tptr); }
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 283 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = NULL; }
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 287 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = (yyvsp[0].tptr); }
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 288 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = NULL; }
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 292 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = (yyvsp[0].tptr); }
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 293 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = NULL; }
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 297 "parser.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-2].tptr)->ntype == Error) {
      (yyval.tptr) = (yyvsp[-2].tptr);
    }
    else if ((yyvsp[0].tptr)->ntype == Error) {
      (yyval.tptr) = (yyvsp[0].tptr);
    }
    else if (!((yyvsp[-2].tptr)->etype == t_Int || (yyvsp[-2].tptr)->etype == t_Char)) {
      errmsg("invalid LHS in assignment");
      (yyval.tptr) = mkErrorNode();
    }
    else if (!((yyvsp[0].tptr)->etype == t_Int || (yyvsp[0].tptr)->etype == t_Char)) {
      errmsg("invalid RHS in assignment");
      (yyval.tptr) = mkErrorNode();
    }
    else {
      (yyval.tptr) = mkExprNode(Assg, t_None, (yyvsp[-2].tptr), (yyvsp[0].tptr));
    }
  }
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 319 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeBinExp(Equals, (yyvsp[-2].tptr), (yyvsp[0].tptr)); }
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 320 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeBinExp(Neq, (yyvsp[-2].tptr), (yyvsp[0].tptr)); }
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 321 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeBinExp(Leq, (yyvsp[-2].tptr), (yyvsp[0].tptr)); }
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 322 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeBinExp(Geq, (yyvsp[-2].tptr), (yyvsp[0].tptr)); }
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 323 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeBinExp(Lt, (yyvsp[-2].tptr), (yyvsp[0].tptr)); }
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 324 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeBinExp(Gt, (yyvsp[-2].tptr), (yyvsp[0].tptr)); }
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 325 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeUnExp(LogicalNot, (yyvsp[0].tptr)); }
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 326 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeBinExp(LogicalAnd, (yyvsp[-2].tptr), (yyvsp[0].tptr)); }
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 327 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeBinExp(LogicalOr, (yyvsp[-2].tptr), (yyvsp[0].tptr)); }
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 328 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = (yyvsp[-1].tptr); }
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 332 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeUnExp(UnaryMinus, (yyvsp[0].tptr)); }
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 333 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeBinExp(Plus, (yyvsp[-2].tptr), (yyvsp[0].tptr)); }
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 334 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeBinExp(BinaryMinus, (yyvsp[-2].tptr), (yyvsp[0].tptr)); }
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 335 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeBinExp(Mult, (yyvsp[-2].tptr), (yyvsp[0].tptr)); }
#line 1879 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 336 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = SynTreeBinExp(Div, (yyvsp[-2].tptr), (yyvsp[0].tptr)); }
#line 1885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 337 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = (yyvsp[0].tptr); }
#line 1891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 338 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = (yyvsp[0].tptr); }
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 339 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = (yyvsp[-1].tptr); }
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 340 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = mkErrorNode(); }
#line 1909 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 341 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = mkConstNode(Intcon, t_Int, ival); }
#line 1915 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 342 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = mkConstNode(Charcon, t_Char, ival); }
#line 1921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 343 "parser.y" /* yacc.c:1646  */
    { yytext[strlen(yytext)-1] = '\0'; /* to remove the trailing " */
               (yyval.tptr) = mkStrNode(strdup(yytext+1)); }
#line 1928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 348 "parser.y" /* yacc.c:1646  */
    {
      bool err_occurred = false;
      stptr = SymTabLookupAll((yyvsp[-2].chptr));
      if (stptr == NULL) {
	err_occurred = true;
        errmsg("%s undeclared", (yyvsp[-2].chptr));
      }
      else {
        if (stptr->type != t_Func) {
	  err_occurred = true;
	  errmsg("%s is not a function", (yyvsp[-2].chptr));
        }
        else {
	  err_occurred = !ActualsMatchFormals(stptr, NULL);
        }
      }

      if (!err_occurred) {
	(yyval.tptr) = mkSymTabRefNode(FunCall, stptr->ret_type, stptr, NULL);
      }
      else {
	(yyval.tptr) = mkErrorNode();
      }
    }
#line 1957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 372 "parser.y" /* yacc.c:1646  */
    {
      bool err_occurred = false;
      stptr = SymTabLookupAll((yyvsp[-3].chptr));
      if (stptr == NULL) {
	err_occurred = true;
        errmsg("%s undeclared", (yyvsp[-3].chptr));
      }
      else if (stptr->type != t_Func) {
	err_occurred = true;
        errmsg("%s is not a function", (yyvsp[-3].chptr));
      }
      else {
	err_occurred = !ActualsMatchFormals(stptr, (yyvsp[-1].tptr));
      }

      if (!err_occurred) {
	(yyval.tptr) = mkSymTabRefNode(FunCall, stptr->ret_type, stptr, (yyvsp[-1].tptr));
      }
      else {
	(yyval.tptr) = mkErrorNode();
      }
    }
#line 1984 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 394 "parser.y" /* yacc.c:1646  */
    {
      stptr = SymTabLookupAll((yyvsp[-3].chptr));
      if (stptr == NULL) {
        errmsg("undeclared identifier %s", (yyvsp[-3].chptr));
      }

      (yyval.tptr) = mkErrorNode();
    }
#line 1997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 405 "parser.y" /* yacc.c:1646  */
    {
      bool err_occurred = false;
      stptr = SymTabLookupAll((yyvsp[-2].chptr));
      if (stptr == NULL) {
        errmsg("undeclared identifier %s", (yyvsp[-2].chptr));
        (yyval.tptr) = mkErrorNode();
      }
      else if (stptr->type != t_Func) {
	err_occurred = true;
        errmsg("%s is not a function", (yyvsp[-2].chptr));
      }
      else if (stptr->ret_type != t_None) {
	err_occurred = true;
	errmsg("non-VOID function %s used in a statement", (yyvsp[-2].chptr));
      }
      else {
	err_occurred = !ActualsMatchFormals(stptr, NULL);
      }

      if (!err_occurred) {
	(yyval.tptr) = mkSymTabRefNode(FunCall, stptr->ret_type, stptr, NULL);
      }
      else {
	(yyval.tptr) = mkErrorNode();
      }
    }
#line 2028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 431 "parser.y" /* yacc.c:1646  */
    {
      bool err_occurred = false;
      stptr = SymTabLookupAll((yyvsp[-3].chptr));
      if (stptr == NULL) {
        errmsg("undeclared identifier %s", (yyvsp[-3].chptr));
        (yyval.tptr) = mkErrorNode();
      }
      else if (stptr->type != t_Func) {
	err_occurred = true;
        errmsg("%s is not a function", (yyvsp[-3].chptr));
      }
      else if (stptr->ret_type != t_None) {
	err_occurred = true;
	errmsg("non-VOID function %s used in a statement", (yyvsp[-3].chptr));
      }
      else {
	err_occurred = !ActualsMatchFormals(stptr, (yyvsp[-1].tptr));
      }

      if (!err_occurred) {
	(yyval.tptr) = mkSymTabRefNode(FunCall, stptr->ret_type, stptr, (yyvsp[-1].tptr));
      }
      else {
	(yyval.tptr) = mkErrorNode();
      }
    }
#line 2059 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 457 "parser.y" /* yacc.c:1646  */
    {
    stptr = SymTabLookupAll((yyvsp[-3].chptr));
    if (stptr == NULL) {
      errmsg("undeclared identifier %s", (yyvsp[-3].chptr));
    }

    (yyval.tptr) = mkErrorNode();
  }
#line 2072 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 468 "parser.y" /* yacc.c:1646  */
    { 
	stptr = SymTabLookupAll((yyvsp[0].chptr));
	if (stptr == NULL) {
	  errmsg("Undeclared variable: %s", (yyvsp[0].chptr));
	  (yyval.tptr) = mkErrorNode();
	}
	else {
	  (yyval.tptr) = mkSymTabRefNode(Var, stptr->type, stptr, NULL);
	}
    }
#line 2087 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 478 "parser.y" /* yacc.c:1646  */
    {
	bool err_occurred = false;

	stptr = SymTabLookupAll((yyvsp[-3].chptr));

	if (stptr == NULL) {
	  errmsg("Undeclared variable: %s", (yyvsp[-3].chptr));
	  err_occurred = true;
	}
	else if (stptr->type != t_Array) {
	  errmsg("%s not declared as an array", (yyvsp[-3].chptr));
	  err_occurred = true;
	}
	if ( !((yyvsp[-1].tptr)->etype == t_Int || (yyvsp[-1].tptr)->etype == t_Char) ) {
	  if ((yyvsp[-1].tptr)->etype != t_Error) {
	    errmsg("subscript to array %s must be of type int or char", (yyvsp[-3].chptr));
	    err_occurred = 1;
	  }
	}

	if (err_occurred) {
	  (yyval.tptr) = mkErrorNode();
	}
	else {
	  (yyval.tptr) = mkSymTabRefNode(ArraySubscript, stptr->elt_type, stptr, (yyvsp[-1].tptr));
	}
    }
#line 2119 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 505 "parser.y" /* yacc.c:1646  */
    {
	stptr = SymTabLookupAll((yyvsp[-3].chptr));

	if (stptr == NULL) {
	  errmsg("Undeclared variable: %s", (yyvsp[-3].chptr));
	}
	else if (stptr->type != t_Array) {
	  errmsg("%s not declared as an array", (yyvsp[-3].chptr));
	}

	(yyval.tptr) = mkErrorNode();
    }
#line 2136 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 520 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = mkListNode((yyvsp[-2].tptr), (yyvsp[0].tptr)); }
#line 2142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 521 "parser.y" /* yacc.c:1646  */
    { (yyval.tptr) = mkListNode((yyvsp[0].tptr), NULL); }
#line 2148 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 524 "parser.y" /* yacc.c:1646  */
    { (yyval.chptr) = id_name; }
#line 2154 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2158 "y.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 526 "parser.y" /* yacc.c:1906  */


