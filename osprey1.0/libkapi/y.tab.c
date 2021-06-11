/* A Bison parser, made from kapi_parser.y
   by GNU bison 1.32.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	ENDMARKER	0
# define	tokARRAY	257
# define	tokBITMASK	258
# define	tokEXPECT	259
# define	tokENUM	260
# define	tokLIMIT	261
# define	tokUSE	262
# define	tokTYPE	263
# define	tokVARIABLE	264
# define	tokATTRIBUTE	265
# define	tokNOREDEFINE	266
# define	tokOF	267
# define	tokIMPLICIT	268
# define	tokNONE	269
# define	tokLCBRACK	270
# define	tokRCBRACK	271
# define	tokLABRACK	272
# define	tokRABRACK	273
# define	tokLSBRACK	274
# define	tokRSBRACK	275
# define	tokLPAREN	276
# define	tokRPAREN	277
# define	tokINT	278
# define	tokREAL	279
# define	tokSTRING	280
# define	tokREALCONST	281
# define	tokINTCONST	282
# define	tokSTRINGCONST	283
# define	tokEQUALS	284
# define	tokCOMMA	285
# define	tokCOLON	286
# define	tokSEMICOLON	287
# define	tokCOLONEQUALS	288
# define	tokPLUSEQUALS	289
# define	tokSTAR	290
# define	tokDOT	291
# define	tokDDOT	292
# define	tokVERTBAR	293
# define	tokCOMMENT	294
# define	tokIDENT	295
# define	tokPLUS	296
# define	tokDIV	297
# define	tokAPPEND	298

#line 24 "kapi_parser.y"


/* static char sccs_id[] = "%W%  %G%  %U%"; */


#include <stdio.h>
#include <string.h>
#include "kapi_internal.h"
#include "kapi_util.h"
#include "kapi_error.h"
#include "kapi_parse.h"

extern knobs_t *kapi_pknobsCurrent;
extern char yytext[];

static vfi_t vfi_gl;
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		147
#define	YYFLAG		-32768
#define	YYNTBASE	46

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 298 ? yytranslate[x] : 89)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
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
       2,     2,     2,     2,     2,     2,     1,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     3,     5,     8,    11,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    32,    36,    39,    48,
      52,    60,    63,    65,    67,    69,    71,    77,    82,    86,
      87,    89,    91,    93,    96,    99,   100,   102,   109,   116,
     118,   120,   122,   124,   129,   130,   132,   134,   136,   140,
     142,   144,   148,   150,   151,   153,   155,   159,   161,   163,
     167,   169,   171,   173,   175,   178,   182,   184,   188,   190,
     193,   195,   197,   202,   204,   205,   207,   208,   210,   213,
     215,   218,   224,   230,   232,   236,   240,   242,   244,   246,
     248,   252
};
static const short yyrhs[] =
{
      -1,    47,     0,    48,     0,    47,    48,     0,    49,    34,
       0,    49,    49,     0,    51,     0,    52,     0,    53,     0,
      54,     0,    56,     0,    57,     0,    60,     0,    50,     0,
       1,     0,    42,    36,    30,     0,    42,    30,     0,    10,
      42,    31,     7,    23,    70,    24,    81,     0,     6,    55,
      70,     0,    45,    42,    31,     7,    23,    70,    24,     0,
      15,    16,     0,    10,     0,    11,     0,     7,     0,    12,
       0,    42,    58,    35,    74,    80,     0,    42,    58,    35,
      75,     0,    21,    59,    22,     0,     0,    42,     0,    37,
       0,    30,     0,    42,    61,     0,    33,    62,     0,     0,
      63,     0,     4,    21,    42,    22,    14,    63,     0,     4,
      21,    27,    22,    14,    63,     0,    27,     0,    25,     0,
      26,     0,    42,     0,     5,    23,    42,    24,     0,     0,
      65,     0,    66,     0,    30,     0,    66,    32,    30,     0,
      68,     0,    28,     0,    68,    32,    28,     0,    71,     0,
       0,    71,     0,    42,     0,    71,    32,    42,     0,    73,
       0,    29,     0,    73,    32,    29,     0,    30,     0,    29,
       0,    28,     0,    79,     0,    42,    58,     0,    76,    78,
      77,     0,    77,     0,    76,    78,    77,     0,    29,     0,
      42,    58,     0,    43,     0,    44,     0,     5,    23,    69,
      24,     0,    82,     0,     0,    83,     0,     0,    84,     0,
      82,    84,     0,    85,     0,    83,    85,     0,     8,    19,
      64,    20,    86,     0,     8,    19,    64,    20,    13,     0,
      13,     0,    23,    87,    24,     0,    23,    88,    24,     0,
      70,     0,    72,     0,    67,     0,    65,     0,    42,    39,
      42,     0,    29,    39,    29,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   140,   142,   145,   147,   150,   152,   157,   159,   160,
     161,   162,   163,   164,   165,   166,   174,   195,   200,   212,
     218,   228,   234,   236,   237,   238,   241,   264,   287,   291,
     296,   300,   303,   312,   327,   331,   336,   340,   346,   351,
     355,   358,   361,   367,   384,   388,   393,   399,   403,   412,
     419,   423,   432,   436,   440,   447,   451,   460,   466,   470,
     480,   492,   503,   514,   517,   547,   566,   570,   584,   592,
     631,   638,   646,   656,   660,   665,   669,   675,   680,   689,
     694,   704,   710,   717,   721,   724,   729,   731,   732,   733,
     736,   751
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "ENDMARKER", "tokARRAY", "tokBITMASK", 
  "tokEXPECT", "tokENUM", "tokLIMIT", "tokUSE", "tokTYPE", "tokVARIABLE", 
  "tokATTRIBUTE", "tokNOREDEFINE", "tokOF", "tokIMPLICIT", "tokNONE", 
  "tokLCBRACK", "tokRCBRACK", "tokLABRACK", "tokRABRACK", "tokLSBRACK", 
  "tokRSBRACK", "tokLPAREN", "tokRPAREN", "tokINT", "tokREAL", 
  "tokSTRING", "tokREALCONST", "tokINTCONST", "tokSTRINGCONST", 
  "tokEQUALS", "tokCOMMA", "tokCOLON", "tokSEMICOLON", "tokCOLONEQUALS", 
  "tokPLUSEQUALS", "tokSTAR", "tokDOT", "tokDDOT", "tokVERTBAR", 
  "tokCOMMENT", "tokIDENT", "tokPLUS", "tokDIV", "tokAPPEND", "file", 
  "stmtlist", "stmt", "stmt0", "attrstmt", "typestmt", "expectstmt", 
  "appendstmt", "implicitstmt", "typeexpect", "assignstmt", 
  "arithmeticassignstmt", "lhsindexexp", "lhsindex", "vardeclstmt", 
  "typespecclause", "fulltypespec", "simpletypespec", "nstringlist", 
  "stringlist", "revstringlist", "reallist", "revreallist", "nidlist", 
  "idlist", "revidlist", "intlist", "revintlist", "rhs", "arithmeticrhs", 
  "arithmeticrhsrest", "intrhs", "arithmeticop", "bitmaskexpr", 
  "nlimitassignlist", "nlimittypelist", "limitassignlist", 
  "limittypelist", "limitassign", "limittype", "limitassignval", 
  "valuelist", "valuerange", NULL
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    46,    46,    47,    47,    48,    48,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    50,    50,    51,    52,
      53,    54,    55,    55,    55,    55,    56,    57,    58,    58,
      59,    59,    59,    60,    61,    61,    62,    62,    62,    63,
      63,    63,    63,    63,    64,    64,    65,    66,    66,    67,
      68,    68,    69,    69,    70,    71,    71,    72,    73,    73,
      74,    74,    74,    74,    74,    75,    76,    76,    77,    77,
      78,    78,    79,    80,    80,    81,    81,    82,    82,    83,
      83,    84,    85,    86,    86,    86,    87,    87,    87,    87,
      88,    88
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     1,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     8,     3,
       7,     2,     1,     1,     1,     1,     5,     4,     3,     0,
       1,     1,     1,     2,     2,     0,     1,     6,     6,     1,
       1,     1,     1,     4,     0,     1,     1,     1,     3,     1,
       1,     3,     1,     0,     1,     1,     3,     1,     1,     3,
       1,     1,     1,     1,     2,     3,     1,     3,     1,     2,
       1,     1,     4,     1,     0,     1,     0,     1,     2,     1,
       2,     5,     5,     1,     3,     3,     1,     1,     1,     1,
       3,     3
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,    15,     0,     0,     0,    35,     0,     0,     3,     0,
      14,     7,     8,     9,    10,    11,    12,    13,    24,    22,
      23,    25,     0,     0,    21,     0,    17,     0,     0,     0,
      33,     0,     4,     5,     6,    55,    19,    54,     0,    32,
      31,    30,     0,     0,     0,    40,    41,    39,    42,    34,
      36,    16,     0,     0,     0,     0,    28,     0,     0,     0,
      62,    61,    60,    29,    74,    27,     0,    66,    63,     0,
      56,     0,     0,     0,     0,    53,    64,     0,    26,    73,
      77,    70,    71,     0,     0,     0,     0,     0,    43,     0,
      52,    44,    78,    68,    29,    65,     0,    76,     0,     0,
      72,    47,     0,    45,    46,    69,    20,     0,    18,    75,
      79,    38,    37,     0,     0,    44,    80,    83,     0,    81,
      48,     0,    50,    58,    55,    89,    88,    49,    86,    87,
      57,     0,     0,     0,     0,     0,     0,     0,    84,    85,
      82,    91,    90,    51,    59,     0,     0,     0
};

static const short yydefgoto[] =
{
     145,     7,     8,     9,    10,    11,    12,    13,    14,    22,
      15,    16,    29,    42,    17,    30,    49,    50,   102,   103,
     104,   126,   127,    89,    36,    37,   129,   130,    64,    65,
      66,    67,    83,    68,    78,   108,    79,   109,    80,   110,
     119,   131,   132
};

static const short yypact[] =
{
       1,-32768,    60,   -23,    17,    33,    15,     8,-32768,    14,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,    16,    44,-32768,   -20,-32768,     0,    46,    43,
  -32768,    50,-32768,-32768,-32768,-32768,-32768,    51,    75,-32768,
  -32768,-32768,    62,    64,    63,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,     7,    80,    47,    65,-32768,   -21,    48,    68,
  -32768,    -5,-32768,    71,    85,-32768,    21,-32768,-32768,    72,
  -32768,    16,    74,    76,    70,    16,    30,    78,-32768,    85,
  -32768,-32768,-32768,    -1,    16,    77,    86,    88,-32768,    79,
      51,    69,-32768,-32768,    71,    36,    81,    96,    35,    35,
  -32768,-32768,    87,-32768,    82,-32768,-32768,    89,-32768,    96,
  -32768,-32768,-32768,    32,    83,    69,-32768,-32768,     2,-32768,
  -32768,    90,-32768,    67,    73,-32768,-32768,    84,-32768,-32768,
      91,    93,    94,    98,    92,    95,    97,    99,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,   109,   115,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,   112,   111,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,   -60,-32768,-32768,-32768,-32768,   -47,     9,     4,
  -32768,-32768,-32768,-32768,   -71,    52,-32768,-32768,-32768,-32768,
  -32768,    49,-32768,-32768,-32768,-32768,-32768,-32768,    54,    20,
  -32768,-32768,-32768
};


#define	YYLAST		137


static const short yytable[] =
{
      85,    -1,     1,    76,    43,    44,    72,     2,    -2,     1,
      39,     3,    59,    96,     2,     1,     4,    40,     3,    23,
       2,    73,    41,     4,     3,    45,    46,    47,    93,     4,
     122,   123,   101,    24,   105,    60,    61,    62,   -68,   -68,
      44,    94,    48,     5,   124,   117,     6,   128,    33,    63,
       5,   111,   112,     6,    25,   118,     5,    31,    35,     6,
      45,    46,    47,    26,    81,    82,    27,    18,   -29,    28,
      19,    20,    21,   -69,   -69,    38,    51,    48,    52,   -67,
     -67,    53,    55,    54,    56,    57,    58,    69,    71,    70,
      74,    75,    25,    77,    88,    84,    86,    91,    87,   101,
      98,    97,    99,   100,   107,   106,   134,   113,   115,   146,
     133,   140,   135,   120,   114,   147,   136,   138,   139,    32,
      34,   141,   125,   137,   121,   143,     0,    90,   144,   116,
       0,     0,    95,    92,     0,     0,     0,   142
};

static const short yycheck[] =
{
      71,     0,     1,    63,     4,     5,    27,     6,     0,     1,
      30,    10,     5,    84,     6,     1,    15,    37,    10,    42,
       6,    42,    42,    15,    10,    25,    26,    27,    29,    15,
      28,    29,    30,    16,    94,    28,    29,    30,    43,    44,
       5,    42,    42,    42,    42,    13,    45,   118,    34,    42,
      42,    98,    99,    45,    21,    23,    42,    42,    42,    45,
      25,    26,    27,    30,    43,    44,    33,     7,    35,    36,
      10,    11,    12,    43,    44,    31,    30,    42,    35,    43,
      44,    31,     7,    32,    22,    21,    23,     7,    23,    42,
      42,    23,    21,     8,    24,    23,    22,    19,    22,    30,
      14,    24,    14,    24,     8,    24,    39,    20,    19,     0,
      20,    13,    39,    30,    32,     0,    32,    24,    24,     7,
       9,    29,   118,    32,   115,    28,    -1,    75,    29,   109,
      -1,    -1,    83,    79,    -1,    -1,    -1,    42
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#ifdef __cplusplus
# define YYSTD(x) std::x
#else
# define YYSTD(x) x
#endif

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
#  define YYSIZE_T YYSTD (size_t)
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#    define YYSIZE_T YYSTD (size_t)
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  ifdef __cplusplus
#   include <cstdlib> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T std::size_t
#  else
#   ifdef __STDC__
#    include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#    define YYSIZE_T size_t
#   endif
#  endif
#  define YYSTACK_ALLOC YYSTD (malloc)
#  define YYSTACK_FREE YYSTD (free)
# endif

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Relocate the TYPE STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Type, Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	yymemcpy ((char *) yyptr, (char *) (Stack),			\
		  yysize * (YYSIZE_T) sizeof (Type));			\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (Type) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# ifdef __cplusplus
#  include <cstddef> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T std::size_t
# else
#  ifdef __STDC__
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
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
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  ifdef __cplusplus
#   include <cstdio>  /* INFRINGES ON USER NAME SPACE */
#  else
#   include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYFPRINTF YYSTD (fprintf)
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace. [The following comment makes no
   sense to me.  Could someone clarify it?  --akim] Since this is
   uninitialized, it does not stop multiple parsers from coexisting.
   */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#if ! defined (yyoverflow) && ! defined (yymemcpy)
# if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#  define yymemcpy __builtin_memcpy
# else				/* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
#  if defined (__STDC__) || defined (__cplusplus)
yymemcpy (char *yyto, const char *yyfrom, YYSIZE_T yycount)
#  else
yymemcpy (yyto, yyfrom, yycount)
     char *yyto;
     const char *yyfrom;
     YYSIZE_T yycount;
#  endif
{
  register const char *yyf = yyfrom;
  register char *yyt = yyto;
  register YYSIZE_T yyi = yycount;

  while (yyi-- != 0)
    *yyt++ = *yyf++;
}
# endif
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 341 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# ifdef __cplusplus
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else /* !__cplusplus */
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif /* !__cplusplus */
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

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
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (short, yyss);
	YYSTACK_RELOCATE (YYSTYPE, yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (YYLTYPE, yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 6:
#line 152 "kapi_parser.y"
{
            kapi_Error( kapi_cLine, 1, "Missing semicolon here or above" );
	}
    break;
case 15:
#line 166 "kapi_parser.y"
{
            kapi_Error( kapi_cLine, 1, "Unknown error here or above" );
	}
    break;
case 16:
#line 175 "kapi_parser.y"
{
	   stn_t *pstn;
           char *pchName, *pchString;

           /* 
              If this is an old KAPI2x BYPASS spec, translate it
              to an INTRACLUSTER bypass NO LONGER SUPPORTED
            */
           if ( 0 == strcmp( yyvsp[-2].pch, "BYPASS" ) ) {
			  kapi_Warning(kapi_cLine,0,"kapi 2.x BYPASS compatability not supported!");
           } 

       pchName = yyvsp[-2].pch;
       pchString = yyvsp[0].pch;
           
	   pstn = kapi_pstnLookup( kapi_pknobsCurrent, pchName );
           kapi_ProcessAttrDecl( pstn, pchString );
	   free(pchName);
	   free(pchString);
	}
    break;
case 17:
#line 195 "kapi_parser.y"
{
            kapi_Error( kapi_cLine, 1, "Missing += or := in stmt" );
	}
    break;
case 18:
#line 204 "kapi_parser.y"
{
	   stn_t *pstn;

	   pstn = kapi_pstnLookup( kapi_pknobsCurrent, yyvsp[-6].pch );
           kapi_ProcessTypeDecl( pstn, yyvsp[-2].pvalhdr, yyvsp[0].plimp ); 
	}
    break;
case 19:
#line 213 "kapi_parser.y"
{
	   kapi_ProcessExpect( yyvsp[0].pvalhdr, yyvsp[-1].iValue );
	}
    break;
case 20:
#line 220 "kapi_parser.y"
{
	   stn_t *pstn;

	   pstn = kapi_pstnLookup( kapi_pknobsCurrent, yyvsp[-5].pch );
           kapi_ProcessAppendDecl( pstn, yyvsp[-1].pvalhdr); 
	}
    break;
case 21:
#line 229 "kapi_parser.y"
{
	   kapi_pknobsCurrent->fImplicitNone = 1;
	}
    break;
case 22:
#line 235 "kapi_parser.y"
{ yyval.iValue = 0; }
    break;
case 23:
#line 236 "kapi_parser.y"
{ yyval.iValue = 1; }
    break;
case 24:
#line 237 "kapi_parser.y"
{ yyval.iValue = 2; }
    break;
case 25:
#line 238 "kapi_parser.y"
{ yyval.iValue = 3; }
    break;
case 26:
#line 242 "kapi_parser.y"
{
	   stn_t *pstn;
           char *pchIdent, *pchIndex, mpchIndex[ 200 ];
 
           if ( 0 == strcmp( yyvsp[-4].pch, "MaxBundleIssue" ) ) {
              pchIdent = kapi_pchCopy( "cluster0MaxBundleIssue" );
              pchIndex = NULL;
           } else if ( 0 == strcmp( yyvsp[-4].pch, "PortMask" ) ) {
              pchIdent = kapi_pchCopy( "cluster0CportMask" );
              sprintf( mpchIndex, "%%%c%s", 'c', yyvsp[-3].pch );
              pchIndex = kapi_pchCopy( mpchIndex );
           } else {
              pchIdent = yyvsp[-4].pch;
              pchIndex = yyvsp[-3].pch;
           }

	   pstn = kapi_pstnLookup( kapi_pknobsCurrent, pchIdent );
	   kapi_ProcessAssignment( pstn, pchIndex, yyvsp[-1].pvalhdr, yyvsp[0].plimp );
	}
    break;
case 27:
#line 265 "kapi_parser.y"
{
	   stn_t *pstn;
           char *pchIdent, *pchIndex, mpchIndex[ 200 ];
 
           if ( 0 == strcmp( yyvsp[-3].pch, "MaxBundleIssue" ) ) {
              pchIdent = kapi_pchCopy( "cluster0MaxBundleIssue" );
              pchIndex = NULL;
           } else if ( 0 == strcmp( yyvsp[-3].pch, "PortMask" ) ) {
              pchIdent = kapi_pchCopy( "cluster0CportMask" );
              sprintf( mpchIndex, "%%%c%s", 'c', yyvsp[-2].pch );
              pchIndex = kapi_pchCopy( mpchIndex );
           } else {
              pchIdent = yyvsp[-3].pch;
              pchIndex = yyvsp[-2].pch;
           }

	   pstn = kapi_pstnLookup( kapi_pknobsCurrent, pchIdent );
	   kapi_ProcessArithmeticAssignment( pstn, pchIndex, yyvsp[0].pvalhdr );
	}
    break;
case 28:
#line 288 "kapi_parser.y"
{
	   yyval.pch = yyvsp[-1].pch;
	}
    break;
case 29:
#line 291 "kapi_parser.y"
{
	   yyval.pch = NULL;
    	}
    break;
case 30:
#line 297 "kapi_parser.y"
{
	   yyval.pch = yyvsp[0].pch;
	}
    break;
case 31:
#line 300 "kapi_parser.y"
{
 	   yyval.pch = kapi_pchCopy( "*" );
	}
    break;
case 32:
#line 303 "kapi_parser.y"
{
           char *pchTmp;
           
           pchTmp = (char *)malloc( sizeof(char)*strlen(yyvsp[0].pch) + 2 );
 	   sprintf( pchTmp, "%%%s", yyvsp[0].pch );
 	   yyval.pch = pchTmp;
	}
    break;
case 33:
#line 313 "kapi_parser.y"
{
	   stn_t *pstn;

           if ( 0 == strcmp( yyvsp[-1].pch, "PortMask" ) ) {
	      pstn = kapi_pstnLookup( kapi_pknobsCurrent, "cluster0CportMask" );
              Declare_cluster0CportMask( pstn );
           } else {
   	      pstn = kapi_pstnLookup( kapi_pknobsCurrent, yyvsp[-1].pch );
	      kapi_ProcessVarDecl( pstn, yyvsp[0].ptfi );
           }
	}
    break;
case 34:
#line 328 "kapi_parser.y"
{
	   yyval.ptfi = yyvsp[0].ptfi;
	}
    break;
case 35:
#line 331 "kapi_parser.y"
{
 	   yyval.ptfi = NULL;
	}
    break;
case 36:
#line 337 "kapi_parser.y"
{
	   yyval.ptfi = yyvsp[0].ptfi;
	}
    break;
case 37:
#line 340 "kapi_parser.y"
{
	   stn_t *pstn;
 
	   pstn = kapi_pstnLookup( kapi_pknobsCurrent, yyvsp[-3].pch );
           yyval.ptfi = ptfiProcessArrayTypeSpec( pstn, yyvsp[0].ptfi );
 	}
    break;
case 38:
#line 346 "kapi_parser.y"
{
           yyval.ptfi = ptfiProcessArrayTypeSpec( yyvsp[-3].pstnA, yyvsp[0].ptfi );
 	}
    break;
case 39:
#line 352 "kapi_parser.y"
{
           yyval.ptfi = &(yyvsp[0].pstnA->u.tfi);
	}
    break;
case 40:
#line 355 "kapi_parser.y"
{
           yyval.ptfi = &(yyvsp[0].pstnA->u.tfi);
	}
    break;
case 41:
#line 358 "kapi_parser.y"
{
           yyval.ptfi = &(yyvsp[0].pstnA->u.tfi);
	}
    break;
case 42:
#line 361 "kapi_parser.y"
{
	   stn_t *pstn;
 
	   pstn = kapi_pstnLookup( kapi_pknobsCurrent, yyvsp[0].pch );
	   yyval.ptfi = kapi_ptfiCheckDeclaredType( pstn );
	}
    break;
case 43:
#line 367 "kapi_parser.y"
{
	   stn_t *pstn;
 
	   pstn = kapi_pstnLookup( kapi_pknobsCurrent, yyvsp[-1].pch );
           if ( pstn->ity == ityTYPENAME 
                && pstn->u.tfi.tty == ttyENUM ) {
	      yyval.ptfi = kapi_ptfiConstructBitmask( &(pstn->u.tfi) );
           } else {
              kapi_Error_pch1( kapi_cLine, 1, 
                               "Base type (%s) of bitmask specification bad", 
                                pstn->pchName );
              yyval.ptfi = NULL;
	   }
	}
    break;
case 44:
#line 385 "kapi_parser.y"
{
	  yyval.pvalhdr = NULL;
	}
    break;
case 45:
#line 388 "kapi_parser.y"
{
 	  yyval.pvalhdr = yyvsp[0].pvalhdr;
 	}
    break;
case 46:
#line 394 "kapi_parser.y"
{
 	   yyval.pvalhdr = pvalhdrMake( ttySTRING, valsLIST, kapi_pvalnReverseTmp( yyvsp[0].pvaln ) );
	}
    break;
case 47:
#line 400 "kapi_parser.y"
{
	   yyval.pvaln = pvalnMakeString( yyvsp[0].pch );
	}
    break;
case 48:
#line 403 "kapi_parser.y"
{
           valn_t *pvaln;

	   pvaln = pvalnMakeString( yyvsp[0].pch );
	   pvaln->pvalnNext = yyvsp[-2].pvaln;
           yyval.pvaln = pvaln;
	}
    break;
case 49:
#line 413 "kapi_parser.y"
{
 	   yyval.pvalhdr = pvalhdrMake( ttyREAL, valsLIST, kapi_pvalnReverseTmp( yyvsp[0].pvaln ) );
	}
    break;
case 50:
#line 420 "kapi_parser.y"
{
	   yyval.pvaln = pvalnMakeReal( yyvsp[0].rValue );
	}
    break;
case 51:
#line 423 "kapi_parser.y"
{
           valn_t *pvaln;

	   pvaln = pvalnMakeReal( yyvsp[0].rValue );
	   pvaln->pvalnNext = yyvsp[-2].pvaln;
           yyval.pvaln = pvaln;
	}
    break;
case 52:
#line 433 "kapi_parser.y"
{
 	   yyval.pvalhdr = pvalhdrMake( ttyIDENT, valsLIST, kapi_pvalnReverseTmp( yyvsp[0].pvaln ) );
	}
    break;
case 53:
#line 436 "kapi_parser.y"
{
	   yyval.pvalhdr = NULL;
	}
    break;
case 54:
#line 441 "kapi_parser.y"
{
 	   yyval.pvalhdr = pvalhdrMake( ttyIDENT, valsLIST, kapi_pvalnReverseTmp( yyvsp[0].pvaln ) );
	}
    break;
case 55:
#line 448 "kapi_parser.y"
{
	   yyval.pvaln = pvalnMakeString( yyvsp[0].pch );
	}
    break;
case 56:
#line 451 "kapi_parser.y"
{
           valn_t *pvaln;

	   pvaln = pvalnMakeString( yyvsp[0].pch );
	   pvaln->pvalnNext = yyvsp[-2].pvaln;
           yyval.pvaln = pvaln;
	}
    break;
case 57:
#line 461 "kapi_parser.y"
{
 	   yyval.pvalhdr = pvalhdrMake( ttyINT, valsLIST, kapi_pvalnReverseTmp( yyvsp[0].pvaln ) );
	}
    break;
case 58:
#line 467 "kapi_parser.y"
{
	   yyval.pvaln = pvalnMakeInt( yyvsp[0].iValue );
	}
    break;
case 59:
#line 470 "kapi_parser.y"
{
           valn_t *pvaln;

	   pvaln = pvalnMakeInt( yyvsp[0].iValue );
	   pvaln->pvalnNext = yyvsp[-2].pvaln;
           yyval.pvaln = pvaln;
	}
    break;
case 60:
#line 481 "kapi_parser.y"
{
           valhdr_t *pvalhdr;
 
           pvalhdr = (valhdr_t *)malloc( sizeof( valhdr_t ) );
           pvalhdr->pvalnList = pvalnMakeString( yyvsp[0].pch );
           pvalhdr->tty = ttySTRING;
           pvalhdr->vals = valsSCALAR;
		   pvalhdr->fRHS=0;

	   yyval.pvalhdr = pvalhdr;
	}
    break;
case 61:
#line 492 "kapi_parser.y"
{
           valhdr_t *pvalhdr;
 
           pvalhdr = (valhdr_t *)malloc( sizeof( valhdr_t ) );
           pvalhdr->pvalnList = pvalnMakeInt( yyvsp[0].iValue );
           pvalhdr->tty = ttyINT;
           pvalhdr->vals = valsSCALAR;
		   pvalhdr->fRHS=0;

	   yyval.pvalhdr = pvalhdr;
	}
    break;
case 62:
#line 503 "kapi_parser.y"
{
           valhdr_t *pvalhdr;
 
           pvalhdr = (valhdr_t *)malloc( sizeof( valhdr_t ) );
           pvalhdr->pvalnList = pvalnMakeReal( yyvsp[0].rValue );
           pvalhdr->tty = ttyREAL;
           pvalhdr->vals = valsSCALAR;
		   pvalhdr->fRHS=0;

	   yyval.pvalhdr = pvalhdr;
	}
    break;
case 63:
#line 514 "kapi_parser.y"
{
	   yyval.pvalhdr = yyvsp[0].pvalhdr;
	}
    break;
case 64:
#line 517 "kapi_parser.y"
{
           stn_t *pstn;

	   pstn = kapi_pstnLookup( kapi_pknobsCurrent, yyvsp[-1].pch );
           if ( pstn->ity == ityUNKNOWN ) {
              kapi_Error_pch1( kapi_cLine, 0, "'%s' unknown identifier", yyvsp[-1].pch );
	      yyval.pvalhdr = NULL;
           } else {
              valhdr_t *pvalhdr;
    
              pvalhdr = (valhdr_t *)malloc( sizeof( valhdr_t ) );
			  pvalhdr->fRHS=1;
              pvalhdr->tty = ttyIDENT;

		    if (yyvsp[0].pch != NULL ) /* if array, get item */  
			{
				ed_t *pedElement;
				pedElement=pedLookup4pstn(pstn,yyvsp[0].pch);
				pvalhdrCopy(pvalhdr,&pedElement->valhdrValue);
				pedElement->valhdrValue.fRHS=1;
			} else
			{
              kapi_LookUpIdent_valhdr( pstn, pvalhdr, 0 );
			}
   
   	      yyval.pvalhdr = pvalhdr;
           }
	}
    break;
case 65:
#line 548 "kapi_parser.y"
{
              valhdr_t *pvalhdr;
			  valn_t *pvalnOp, *pvalnExp, *pvalnVal;

              pvalhdr = (valhdr_t *)malloc( sizeof( valhdr_t ) );
              pvalhdr->tty = ttyEXPRESSION;
			  pvalhdr->vals = valsLIST;
			  pvalnVal=yyvsp[0].pvaln;
			  pvalnOp=yyvsp[-1].pvaln;
			  pvalnExp=yyvsp[-2].pvaln;
			  pvalnVal->pvalnNext=pvalnOp;
			  pvalnOp->pvalnNext=pvalnExp;

			  pvalhdr->pvalnList=pvalnVal;
       	      yyval.pvalhdr = pvalhdr;
	}
    break;
case 66:
#line 567 "kapi_parser.y"
{ 
		yyval.pvaln=yyvsp[0].pvaln;
	}
    break;
case 67:
#line 570 "kapi_parser.y"
{
			  valn_t *pvalnOp, *pvalnExp, *pvalnVal;

			  pvalnVal=yyvsp[0].pvaln;
			  pvalnOp=yyvsp[-1].pvaln;
			  pvalnExp=yyvsp[-2].pvaln;
			  pvalnVal->pvalnNext=pvalnOp;
			  pvalnOp->pvalnNext=pvalnExp;

       	      yyval.pvaln = pvalnVal;
	}
    break;
case 68:
#line 585 "kapi_parser.y"
{
           valn_t *pvaln;
 
           pvaln = pvalnMakeInt( yyvsp[0].iValue );

	   yyval.pvaln = pvaln;
	}
    break;
case 69:
#line 592 "kapi_parser.y"
{
           stn_t *pstn;

	   pstn = kapi_pstnLookup( kapi_pknobsCurrent, yyvsp[-1].pch );
           if ( pstn->ity == ityUNKNOWN ) {
              kapi_Error_pch1( kapi_cLine, 0, "'%s' unknown identifier", yyvsp[-1].pch );
	          yyval.pvaln = NULL;
           } else 
		   {
              valhdr_t *pvalhdr;
			  pvalhdr = (valhdr_t *)malloc( sizeof( valhdr_t ) );

		    if (pstn->u.vfi.ptfi->tty == ttyARRAY) /* if array, get item */  
			{
				ed_t *pedElement;
				pedElement=pedLookup4pstn(pstn,yyvsp[0].pch);
				pvalhdrCopy(pvalhdr,&pedElement->valhdrValue);
				pedElement->valhdrValue.fRHS=1;
			} else
			{
              kapi_LookUpIdent_valhdr( pstn, pvalhdr, 0 );
			}

			  /* now pvalhdr holds the value for the variable */
			  if ((pvalhdr->tty!=ttyINT) || (pvalhdr->vals!=valsSCALAR)) {
                 kapi_Error_pch1( kapi_cLine, 0, "'%s' is non integer used in arithmetic expression", yyvsp[-1].pch );
				 yyval.pvaln = NULL;
			  } else
			  {
				 valn_t *pvaln;
				 pvaln = pvalnMakeInt(pvalhdr->pvalnList->val.i);
				 /* mark value as used on RHS of equation */
				 pstn->fRHS=1;
   				 yyval.pvaln = pvaln;
			  }
           }
	}
    break;
case 70:
#line 632 "kapi_parser.y"
{
		valn_t *pvaln;
		pvaln=pvalnMakeArithmeticOp(yyvsp[0].pch);

	   yyval.pvaln = pvaln;
	}
    break;
case 71:
#line 638 "kapi_parser.y"
{
		valn_t *pvaln;
		pvaln=pvalnMakeArithmeticOp(yyvsp[0].pch);

	   yyval.pvaln = pvaln;
	}
    break;
case 72:
#line 647 "kapi_parser.y"
{
           valhdr_t *pvalhdr;
    
           pvalhdr = (valhdr_t *)malloc( sizeof( valhdr_t ) );
           ProcessBitmaskExpr( pvalhdr, yyvsp[-1].pvalhdr );
	   yyval.pvalhdr = pvalhdr;
	}
    break;
case 73:
#line 657 "kapi_parser.y"
{
           yyval.plimp = yyvsp[0].plimp;
	}
    break;
case 74:
#line 660 "kapi_parser.y"
{
           yyval.plimp = NULL;
 	}
    break;
case 75:
#line 666 "kapi_parser.y"
{ 
           yyval.plimp = yyvsp[0].plimp; 
 	}
    break;
case 76:
#line 669 "kapi_parser.y"
{ 
           yyval.plimp = NULL; 
        }
    break;
case 77:
#line 676 "kapi_parser.y"
{ 
           yyvsp[0].plimp->plimpNext = NULL; 
           yyval.plimp = yyvsp[0].plimp; 
	}
    break;
case 78:
#line 680 "kapi_parser.y"
{
           limp_t *plimpTmp;
  
           plimpTmp = yyvsp[0].plimp;
           plimpTmp->plimpNext = yyvsp[-1].plimp;
	   yyval.plimp = plimpTmp;
 	}
    break;
case 79:
#line 690 "kapi_parser.y"
{ 
           yyvsp[0].plimp->plimpNext = NULL; 
           yyval.plimp = yyvsp[0].plimp; 
	}
    break;
case 80:
#line 694 "kapi_parser.y"
{
           limp_t *plimpTmp;
  
           plimpTmp = yyvsp[0].plimp;
           plimpTmp->plimpNext = yyvsp[-1].plimp;
	   yyval.plimp = plimpTmp;
 	}
    break;
case 81:
#line 705 "kapi_parser.y"
{
  	   yyval.plimp = plimpProcessLimitVariable( yyvsp[-2].pvalhdr, yyvsp[0].pvalhdr );
        }
    break;
case 82:
#line 711 "kapi_parser.y"
{
  	   yyval.plimp = plimpProcessLimitType( yyvsp[-2].pvalhdr );
   	}
    break;
case 83:
#line 718 "kapi_parser.y"
{
	   yyval.pvalhdr = pvalhdrMake( ttyUNKNOWN, valsNOREDEFINE, NULL );
	}
    break;
case 84:
#line 721 "kapi_parser.y"
{
	   yyval.pvalhdr = yyvsp[-1].pvalhdr;
	}
    break;
case 85:
#line 724 "kapi_parser.y"
{
	   yyval.pvalhdr = yyvsp[-1].pvalhdr;
	}
    break;
case 86:
#line 730 "kapi_parser.y"
{ yyval.pvalhdr = yyvsp[0].pvalhdr; }
    break;
case 87:
#line 731 "kapi_parser.y"
{ yyval.pvalhdr = yyvsp[0].pvalhdr; }
    break;
case 88:
#line 732 "kapi_parser.y"
{ yyval.pvalhdr = yyvsp[0].pvalhdr; }
    break;
case 89:
#line 733 "kapi_parser.y"
{ yyval.pvalhdr = yyvsp[0].pvalhdr; }
    break;
case 90:
#line 737 "kapi_parser.y"
{
           valn_t *pvaln1, *pvaln2;
           stn_t *pstn1, *pstn2;

           /* create entries, but do not use pointers */
           pstn1 = kapi_pstnLookup( kapi_pknobsCurrent, yyvsp[-2].pch );
           pstn2 = kapi_pstnLookup( kapi_pknobsCurrent, yyvsp[0].pch );

           pvaln1 = pvalnMakeIdent( yyvsp[-2].pch );
           pvaln2 = pvalnMakeIdent( yyvsp[0].pch );
           pvaln1->pvalnNext = pvaln2;
           pvaln2->pvalnNext = NULL;
	   yyval.pvalhdr = pvalhdrMake( ttyIDENT, valsRANGE, pvaln1 );
        }
    break;
case 91:
#line 751 "kapi_parser.y"
{
           valn_t *pvaln1, *pvaln2;

           pvaln1 = pvalnMakeInt( yyvsp[-2].iValue );
           pvaln2 = pvalnMakeInt( yyvsp[0].iValue );
           pvaln1->pvalnNext = pvaln2;
           pvaln2->pvalnNext = NULL;
	   yyval.pvalhdr = pvalhdrMake( ttyINT, valsRANGE, pvaln1 );
        }
    break;
}

#line 727 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 762 "kapi_parser.y"


