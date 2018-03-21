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
#line 6 "parser.yacc" /* yacc.c:339  */



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

extern FILE *yyin;
extern int lineno;
extern int comment_nesting;
int isfunction=0;
int scope=0;

int flag = 0;
int errorFlag=0;
struct stable{
	char name[100];
	char type[50];
	long long int scope;
    int fundef;
    int countargs;
    char argslist[20];
    int storage;
};
struct ctable{
	char name[100];
	char type[50];
};
extern struct stable symbol_table[100000];
extern struct ctable constant_table[100000];
extern char yyval[100];
extern char yycons[100];
extern char yystr[100];
extern char currtype[100],prevtype[100],currid[100],previd[100];
char fnname[100];
char fnlist[20];
int fncount=0;
char fncname[100];
char fnclist[20];
int fnccount=0;
char* getcurrid();
char* getcurrtype();
char* getprevid();
char* getprevtype();
char gettype(char *name);


	void insert_symbol_table()
	{
	    int k=hash_cal(yyval);
			struct stable temp;
			strcpy(temp.name,yyval);
            temp.countargs=0;
            char* tmp = getcurrtype();
            strcpy(temp.type,tmp);
            if(tmp[0]=='i')
            {
            	temp.storage=4;
            }
            else if(tmp[0]=='f')
            {
            	temp.storage=8;
            }
            else
            {
            	temp.storage=0;
            }
			if(isfunction==1)
            {
                temp.fundef=1;
            }
            else
            {
                temp.fundef=0;
            }
			int tempscope=scope;
			temp.scope=tempscope;
			int i=0;
			int flag=0;
			for(i=0;i<1000;i++)
			{
				if(symbol_table[k].name[0]=='\0')
				{
					break;
				}
				else
				{
					
					if(strcmp(yyval,symbol_table[k].name)==0 && temp.scope==symbol_table[k].scope)
					{
						flag=1;
						printf("Error:redeclaration\n");
						break;
					}
					k=(k+1)%1000;
				}
			}
			if(flag==0)
			{
				symbol_table[k]=temp;
			}	
	}
    int ck_symbol_table()
	{
	    int k=hash_cal(yyval);
			struct stable temp;
			strcpy(temp.name,yyval);
			strcpy(temp.type,"identifier");

			int tempscope=scope;
			temp.scope=tempscope;
			int i=0;
			int flag=0;

			for(i=0;i<1000;i++)
			{
				if(strcmp(yyval,symbol_table[i].name)==0)
                {
                    
                    return(1);
                }
			}
            printf("%s -->",yyval);
              return(0);
			
	}

    int sym_update_fundef()
	{
	  
			int i=0;
			int flag=0;

			for(i=0;i<1000;i++)
			{
				if(strcmp(fnname,symbol_table[i].name)==0&&symbol_table[i].fundef==1)
                {
                    symbol_table[i].countargs=fncount;
                    strcpy(symbol_table[i].argslist,fnlist);
                    return(1);
                }
			}
            return(0);
            
			
	}
    int sym_ck_funcall()
	{
           // printf("Checking %s %s ",fncname,fnclist);
			int i=0;
			int flag=0;
			for(i=0;i<1000;i++)
			{
				if(strcmp(fncname,symbol_table[i].name)==0&&symbol_table[i].fundef==1&&strcmp(fnclist,symbol_table[i].argslist)==0)
                {
                    return(1);
                }
			}
            return(0);
            
			
	}
    void copyfnname()
	{
	    int k=hash_cal(yyval);
			struct stable temp;
			strcpy(fnname,yyval);
						
	}
    
     void copyfncname()
	{
	    int k=hash_cal(yyval);
			struct stable temp;
			strcpy(fncname,yyval);
						
	}
	void insert_constant_table()
	{
	    int k=hash_cal(yycons);
		struct ctable temp;
		strcpy(temp.name,yycons);
		strcpy(temp.type,"numeric constant");
		int i=0;
		int flag=0;
		for(i=0;i<1000;i++)
		{
			if(constant_table[k].name[0]=='\0')
			{
				break;
			}
			else
			{
				if(strcmp(yycons,constant_table[k].name)==0)
				{
					flag=1;
					break;
				}
				k=(k+1)%1000;
			}
		}
		if(flag==0)
		{
			constant_table[k]=temp;
		}
	}
	void insert_constant_table_str()
	{
	    int k=hash_cal(yystr);
		struct ctable temp;
		strcpy(temp.name,yystr);
		strcpy(temp.type,"string constant");
		int i=0;
		int flag=0;
		for(i=0;i<1000;i++)
		{
			if(constant_table[k].name[0]=='\0')
			{
				break;
			}
			else
			{
				if(strcmp(yystr,constant_table[k].name)==0)
				{
					flag=1;
					break;
				}
				k=(k+1)%1000;
			}
		}
		if(flag==0)
		{
			constant_table[k]=temp;
		}
	}   

    void delete_sym(int n)
    {
        int i;
        for(i=0;i<1000;i++)
        {
            if(symbol_table[i].name[0]!='\0'&&symbol_table[i].scope==n)
            {
                printf("ENTRY DELETED::%s   %s  %d \n",symbol_table[i].name,symbol_table[i].type,symbol_table[i].scope);
                symbol_table[i].name[0]='\0';
                symbol_table[i].type[0]!='\0';

            }
        }
    }          


#line 320 "y.tab.c" /* yacc.c:339  */

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
    AUTO = 258,
    BREAK = 259,
    CASE = 260,
    CHAR = 261,
    CONTINUE = 262,
    DEFAULT = 263,
    DO = 264,
    DOUBLE = 265,
    ELSE = 266,
    ENUM = 267,
    EXTERN = 268,
    FLOAT = 269,
    FOR = 270,
    GOTO = 271,
    IF = 272,
    INT = 273,
    LONG = 274,
    REGISTER = 275,
    RETURN = 276,
    SHORT = 277,
    SIGNED = 278,
    SIZEOF = 279,
    STATIC = 280,
    STRUCT = 281,
    SWITCH = 282,
    TYPEDEF = 283,
    UNION = 284,
    UNSIGNED = 285,
    VOID = 286,
    VOLATILE = 287,
    WHILE = 288,
    IDENTIFIER = 289,
    STRING_LITERAL = 290,
    ASSIGN_OP = 291,
    REL_OP = 292,
    ADD_OP = 293,
    MUL_OP = 294,
    INCDEC_OP = 295,
    EQU_OP = 296,
    LAND = 297,
    LOR = 298,
    BAND = 299,
    BXOR = 300,
    BOR = 301,
    NOT_OP = 302,
    INTVALUE = 303,
    FLOATVALUE = 304,
    LOWER_THAN_ELSE = 305
  };
#endif
/* Tokens.  */
#define AUTO 258
#define BREAK 259
#define CASE 260
#define CHAR 261
#define CONTINUE 262
#define DEFAULT 263
#define DO 264
#define DOUBLE 265
#define ELSE 266
#define ENUM 267
#define EXTERN 268
#define FLOAT 269
#define FOR 270
#define GOTO 271
#define IF 272
#define INT 273
#define LONG 274
#define REGISTER 275
#define RETURN 276
#define SHORT 277
#define SIGNED 278
#define SIZEOF 279
#define STATIC 280
#define STRUCT 281
#define SWITCH 282
#define TYPEDEF 283
#define UNION 284
#define UNSIGNED 285
#define VOID 286
#define VOLATILE 287
#define WHILE 288
#define IDENTIFIER 289
#define STRING_LITERAL 290
#define ASSIGN_OP 291
#define REL_OP 292
#define ADD_OP 293
#define MUL_OP 294
#define INCDEC_OP 295
#define EQU_OP 296
#define LAND 297
#define LOR 298
#define BAND 299
#define BXOR 300
#define BOR 301
#define NOT_OP 302
#define INTVALUE 303
#define FLOATVALUE 304
#define LOWER_THAN_ELSE 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 471 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   383

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      54,    55,     2,     2,    53,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    56,    52,
       2,    51,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,     2,    58,     2,     2,     2,     2,
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   281,   281,   282,   286,   287,   291,   295,   299,   300,
     301,   305,   306,   310,   311,   315,   316,   320,   321,   325,
     329,   333,   334,   337,   340,   341,   345,   346,   352,   353,
     354,   355,   356,   357,   358,   359,   365,   366,   370,   371,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     398,   401,   404,   405,   408,   409,   415,   416,   417,   423,
     424,   425,   426,   430,   431,   432,   433,   437,   441,   446,
     450,   453
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AUTO", "BREAK", "CASE", "CHAR",
  "CONTINUE", "DEFAULT", "DO", "DOUBLE", "ELSE", "ENUM", "EXTERN", "FLOAT",
  "FOR", "GOTO", "IF", "INT", "LONG", "REGISTER", "RETURN", "SHORT",
  "SIGNED", "SIZEOF", "STATIC", "STRUCT", "SWITCH", "TYPEDEF", "UNION",
  "UNSIGNED", "VOID", "VOLATILE", "WHILE", "IDENTIFIER", "STRING_LITERAL",
  "ASSIGN_OP", "REL_OP", "ADD_OP", "MUL_OP", "INCDEC_OP", "EQU_OP", "LAND",
  "LOR", "BAND", "BXOR", "BOR", "NOT_OP", "INTVALUE", "FLOATVALUE",
  "LOWER_THAN_ELSE", "'='", "';'", "','", "'('", "')'", "':'", "'{'",
  "'}'", "$accept", "PROGRAM", "EXTERNAL_DECLARATION", "DECLARATION",
  "DECLARATION_SPECIFIER", "TYPE_SPECIFIER", "INIT_DECLARATOR_LIST",
  "INIT_DECLARATOR", "DECLARATOR", "FUNCTION_DEFINITION", "FND_OPN",
  "FND_CLS", "DEFINITION_SPECIFIER_LIST", "VARIABLE_DECLARATION",
  "COMPOUND_STATEMENT", "STATEMENT_LIST", "STATEMENT", "LABELED_STATEMENT",
  "EXPRESSION_STATEMENT", "EXPRESSION", "FUNCTION_CALL", "FNC_OPN",
  "FUNCTION_CALL_CONTD", "EXPRESSION_LIST", "SELECTION_STATEMENT",
  "ITERATION_STATEMENT", "JUMP_STATEMENT", "OP_BRACE", "CL_BRACE", "DECID",
  "FUNDECID", "EXPID", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,    61,    59,    44,    40,    41,    58,   123,   125
};
# endif

#define YYPACT_NINF -114

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-114)))

#define YYTABLE_NINF -81

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      41,  -114,  -114,  -114,     2,  -114,  -114,   -15,  -114,  -114,
    -114,  -114,   -48,    11,   -31,  -114,   -42,  -114,   -16,  -114,
     -14,  -114,    11,   168,  -114,   -13,  -114,  -114,  -114,  -114,
      13,   168,  -114,  -114,   168,   300,  -114,    64,  -114,    16,
       5,   -40,  -114,  -114,  -114,   198,   168,   168,   168,   168,
     168,   168,   168,   168,   168,   168,  -114,   168,  -114,     9,
    -114,  -114,  -114,   102,    41,     5,  -114,    58,    21,  -114,
      15,   320,   310,    40,   339,   330,   300,   300,  -114,   300,
    -114,    -7,    14,    19,   168,    24,    17,   157,    31,    34,
      35,    39,    51,  -114,  -114,  -114,    11,  -114,   102,  -114,
    -114,  -114,   288,  -114,  -114,  -114,  -114,  -114,  -114,   168,
    -114,  -114,  -114,   182,  -114,   157,    75,   133,   168,  -114,
     300,   168,   168,  -114,  -114,  -114,   300,   157,  -114,    60,
     133,   213,   228,   243,  -114,   168,    91,   157,   157,   157,
     258,   157,   273,   110,  -114,  -114,    70,  -114,   157,   157,
    -114,  -114,  -114
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    10,     9,     8,     0,     2,     5,     0,     7,     4,
       1,     3,    79,     0,     0,    11,    13,    15,     0,    79,
       0,     6,     0,     0,    19,     0,    16,    12,    81,    59,
       0,     0,    56,    57,     0,    14,    58,    55,    20,     0,
       0,     0,    21,    52,    51,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    53,     0,    61,     0,
      23,    77,    17,     0,     0,     0,    54,    43,    44,    45,
      42,    46,    47,    49,    50,    48,    40,    41,    62,    65,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    38,    78,    34,     0,    29,     0,    27,
      28,    30,     0,    32,    31,    33,    25,    22,    18,     0,
      63,    35,    74,     0,    73,     0,     0,     0,     0,    75,
      76,     0,     0,    26,    24,    39,    64,     0,    37,     0,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,    66,    68,    69,     0,    71,     0,     0,
      70,    72,    67
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -114,  -114,   120,     3,    10,  -114,  -114,   105,   115,  -114,
    -114,    89,  -114,    68,   -28,  -114,   -47,  -114,  -113,   -23,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,    36,  -114,
    -114,   111
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,    95,    96,     8,    14,    15,    16,     9,
      25,    40,    41,    42,    97,    98,    99,   100,   101,   102,
      36,    59,    80,    81,   103,   104,   105,    63,   106,    17,
      18,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,     1,    10,     6,   130,     2,   -80,     6,    44,    23,
       7,    45,    62,    64,     7,    38,     1,   136,     3,    12,
       2,    21,    22,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,     3,    77,    39,    79,   108,    24,    13,
     116,    26,    38,    28,    29,    19,   109,    28,   110,    30,
      60,   123,    46,    47,    48,     1,    31,    32,    33,     2,
      48,   113,    61,    34,    78,    13,   111,   120,   128,    28,
      29,   112,     3,   115,    39,    30,   114,    46,    47,    48,
     134,    49,    31,    32,    33,   117,   126,   119,   118,    34,
     143,   144,   145,   121,   147,   131,    47,    48,   132,   133,
      55,   151,   152,    82,    56,   122,    83,    84,   129,    85,
      86,    87,   140,   142,   135,    57,     1,    88,    58,    89,
       2,   149,   150,    90,    11,    28,    29,    27,    20,    91,
      65,    30,   107,     3,   124,    92,    28,    29,    31,    32,
      33,    43,    30,     0,     0,    34,   141,     0,     0,    31,
      32,    33,     0,     0,    93,     0,    34,     0,    82,    61,
      94,    83,    84,     0,    85,    86,    87,    28,    29,     0,
       0,     1,    88,    30,    89,     2,     0,     0,    90,     0,
      31,    32,    33,     0,    91,    93,     0,    34,     3,     0,
      92,    28,    29,     0,     0,     0,     0,    30,     0,     0,
       0,     0,    28,    29,    31,    32,    33,     0,    30,    93,
       0,    34,     0,     0,    61,    31,    32,    33,     0,    46,
      47,    48,    34,    49,    50,    51,    52,    53,    54,     0,
       0,     0,     0,     0,     0,    46,    47,    48,   127,    49,
      50,    51,    52,    53,    54,     0,     0,     0,     0,     0,
      46,    47,    48,    66,    49,    50,    51,    52,    53,    54,
       0,     0,     0,     0,     0,    46,    47,    48,   137,    49,
      50,    51,    52,    53,    54,     0,     0,     0,     0,     0,
      46,    47,    48,   138,    49,    50,    51,    52,    53,    54,
       0,     0,     0,     0,     0,    46,    47,    48,   139,    49,
      50,    51,    52,    53,    54,     0,     0,     0,     0,     0,
      46,    47,    48,   146,    49,    50,    51,    52,    53,    54,
       0,     0,     0,     0,     0,    46,    47,    48,   148,    49,
      50,    51,    52,    53,    54,     0,     0,    46,    47,    48,
     125,    49,    50,    51,    52,    53,    54,    46,    47,    48,
       0,    49,    50,     0,    52,    53,    54,    46,    47,    48,
       0,    49,     0,     0,    52,    53,    54,    46,    47,    48,
       0,    49,     0,     0,    52,    53,    46,    47,    48,     0,
      49,     0,     0,    52
};

static const yytype_int16 yycheck[] =
{
      23,    14,     0,     0,   117,    18,    54,     4,    31,    51,
       0,    34,    40,    53,     4,    55,    14,   130,    31,    34,
      18,    52,    53,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    31,    57,    25,    59,    65,    54,    54,
      87,    55,    55,    34,    35,    34,    53,    34,    55,    40,
      34,    98,    37,    38,    39,    14,    47,    48,    49,    18,
      39,    84,    57,    54,    55,    54,    52,    90,   115,    34,
      35,    52,    31,    56,    64,    40,    52,    37,    38,    39,
     127,    41,    47,    48,    49,    54,   109,    52,    54,    54,
     137,   138,   139,    54,   141,   118,    38,    39,   121,   122,
      36,   148,   149,     1,    40,    54,     4,     5,    33,     7,
       8,     9,   135,   136,    54,    51,    14,    15,    54,    17,
      18,    11,    52,    21,     4,    34,    35,    22,    13,    27,
      41,    40,    64,    31,    98,    33,    34,    35,    47,    48,
      49,    30,    40,    -1,    -1,    54,    55,    -1,    -1,    47,
      48,    49,    -1,    -1,    52,    -1,    54,    -1,     1,    57,
      58,     4,     5,    -1,     7,     8,     9,    34,    35,    -1,
      -1,    14,    15,    40,    17,    18,    -1,    -1,    21,    -1,
      47,    48,    49,    -1,    27,    52,    -1,    54,    31,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    34,    35,    47,    48,    49,    -1,    40,    52,
      -1,    54,    -1,    -1,    57,    47,    48,    49,    -1,    37,
      38,    39,    54,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    39,    56,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    55,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    37,    38,    39,    55,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    55,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    37,    38,    39,    55,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      37,    38,    39,    55,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    37,    38,    39,    55,    41,
      42,    43,    44,    45,    46,    -1,    -1,    37,    38,    39,
      52,    41,    42,    43,    44,    45,    46,    37,    38,    39,
      -1,    41,    42,    -1,    44,    45,    46,    37,    38,    39,
      -1,    41,    -1,    -1,    44,    45,    46,    37,    38,    39,
      -1,    41,    -1,    -1,    44,    45,    37,    38,    39,    -1,
      41,    -1,    -1,    44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    18,    31,    60,    61,    62,    63,    64,    68,
       0,    61,    34,    54,    65,    66,    67,    88,    89,    34,
      67,    52,    53,    51,    54,    69,    55,    66,    34,    35,
      40,    47,    48,    49,    54,    78,    79,    90,    55,    63,
      70,    71,    72,    90,    78,    78,    37,    38,    39,    41,
      42,    43,    44,    45,    46,    36,    40,    51,    54,    80,
      34,    57,    73,    86,    53,    70,    55,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    55,    78,
      81,    82,     1,     4,     5,     7,     8,     9,    15,    17,
      21,    27,    33,    52,    58,    62,    63,    73,    74,    75,
      76,    77,    78,    83,    84,    85,    87,    72,    73,    53,
      55,    52,    52,    78,    52,    56,    75,    54,    54,    52,
      78,    54,    54,    75,    87,    52,    78,    56,    75,    33,
      77,    78,    78,    78,    75,    54,    77,    55,    55,    55,
      78,    55,    78,    75,    75,    75,    55,    75,    55,    11,
      52,    75,    75
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    60,    61,    61,    62,    63,    64,    64,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      70,    71,    71,    72,    73,    73,    74,    74,    75,    75,
      75,    75,    75,    75,    75,    75,    76,    76,    77,    77,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      79,    80,    81,    81,    82,    82,    83,    83,    83,    84,
      84,    84,    84,    85,    85,    85,    85,    86,    87,    88,
      89,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     3,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     3,     5,     6,     1,
       1,     1,     3,     2,     3,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     4,     3,     1,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     3,     1,     1,     1,     1,     1,
       3,     1,     1,     2,     3,     1,     5,     7,     5,     5,
       7,     6,     7,     2,     2,     2,     2,     1,     1,     1,
       1,     1
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
        case 14:
#line 311 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[0])==-1) printf("Invalid Expression\n");}
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 320 "parser.yacc" /* yacc.c:1646  */
    {sym_update_fundef();fncount=0;fnlist[0]='\0';}
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 321 "parser.yacc" /* yacc.c:1646  */
    {sym_update_fundef();fncount=0;fnlist[0]='\0';}
#line 1724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 325 "parser.yacc" /* yacc.c:1646  */
    {scope++;}
#line 1730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 329 "parser.yacc" /* yacc.c:1646  */
    {scope--;}
#line 1736 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 333 "parser.yacc" /* yacc.c:1646  */
    {fnlist[fncount++]=getcurrtype()[0];fnlist[fncount]='\0';if(getcurrtype()[0]=='v'){printf("ERROR:function argument cannot be void.\n");}}
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 334 "parser.yacc" /* yacc.c:1646  */
    {fnlist[fncount++]=getcurrtype()[0];fnlist[fncount]='\0';if(getcurrtype()[0]=='v'){printf("ERROR:function argument cannot be void.\n");}}
#line 1748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 337 "parser.yacc" /* yacc.c:1646  */
    {insert_symbol_table();}
#line 1754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 365 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==-1) printf("Invalid Expression\n");}
#line 1760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 371 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-1])==-1) printf("Invalid Expression\n");}
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 375 "parser.yacc" /* yacc.c:1646  */
    { if((yyvsp[0])==1 && (yyvsp[-2])==(yyvsp[0]))(yyval)=1; else if((yyvsp[0])==2 && (yyvsp[-2])==(yyvsp[0]))(yyval)=2; else (yyval)=-1;}
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 376 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[0])==1 && (yyvsp[-2])==(yyvsp[0]))(yyval)=1; else if((yyvsp[0])==2 && (yyvsp[-2])==(yyvsp[0]))(yyval)=2; else (yyval)=-1;}
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 377 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-2])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;}
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 378 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-2])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;}
#line 1790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 379 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-2])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;}
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 380 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-2])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;}
#line 1802 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 381 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-2])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;}
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 382 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-2])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;}
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 383 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-2])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;}
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 384 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-2])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;}
#line 1826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 385 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-2])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;}
#line 1832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 386 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[0])==1)(yyval)=1; else if((yyvsp[0])==2)(yyval)=2; else (yyval)=-1;}
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 387 "parser.yacc" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1844 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 388 "parser.yacc" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 1850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 389 "parser.yacc" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 1856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 390 "parser.yacc" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 391 "parser.yacc" /* yacc.c:1646  */
    {insert_constant_table(); (yyval)=1;}
#line 1868 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 392 "parser.yacc" /* yacc.c:1646  */
    {insert_constant_table(); (yyval)=2;}
#line 1874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 393 "parser.yacc" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]); if((yyvsp[0])==-1)(yyval)=3;}
#line 1880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 394 "parser.yacc" /* yacc.c:1646  */
    {insert_constant_table_str(); (yyval)=-1;}
#line 1886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 398 "parser.yacc" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-2]);if(!sym_ck_funcall()){printf("Error:function defination does not match any existing function definations\n");}fnccount=0;fnclist[0]='\0';}
#line 1892 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 401 "parser.yacc" /* yacc.c:1646  */
    {copyfncname();}
#line 1898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 408 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[0])==-1) printf("Invalid Expression\n");else if((yyvsp[0])==1){fnclist[fnccount++]='i';fnclist[fnccount]='\0';}else if((yyvsp[0])==2){fnclist[fnccount++]='f';fnclist[fnccount]='\0';}}
#line 1904 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 409 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[0])==-1) printf("Invalid Expression\n");else if((yyvsp[0])==1){fnclist[fnccount++]='i';fnclist[fnccount]='\0';}else if((yyvsp[0])==2){fnclist[fnccount++]='f';fnclist[fnccount]='\0';}}
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 415 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==-1) printf("Invalid Expression\n");}
#line 1916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 416 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-4])==-1) printf("Invalid Expression\n");}
#line 1922 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 417 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==-1) printf("Invalid Expression\n");}
#line 1928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 423 "parser.yacc" /* yacc.c:1646  */
    { if((yyvsp[-2])==-1) printf("Invalid Expression\n");else if((yyvsp[-2])!=1){printf("While should have a interger expression\n");}}
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 424 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==-1) printf("Invalid Expression\n");}
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 426 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==-1) printf("Invalid Expression\n");}
#line 1946 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 432 "parser.yacc" /* yacc.c:1646  */
    {if(gettype(fnname)!='v'){printf("Error Return type wrong.\n");}}
#line 1952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 433 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[0])==-1) printf("Invalid Expression\n");else if(((yyvsp[0])==1&& gettype(fnname)!='i') || ((yyvsp[0])==2 && gettype(fnname)!='f') ){printf("Error Return type wrong.\n");}}
#line 1958 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 437 "parser.yacc" /* yacc.c:1646  */
    {scope++;}
#line 1964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 441 "parser.yacc" /* yacc.c:1646  */
    {delete_sym(scope);scope--;}
#line 1970 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 446 "parser.yacc" /* yacc.c:1646  */
    {insert_symbol_table();}
#line 1976 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 450 "parser.yacc" /* yacc.c:1646  */
    {isfunction=1;copyfnname();insert_symbol_table();isfunction=0;}
#line 1982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 453 "parser.yacc" /* yacc.c:1646  */
    {

                if(gettype(getcurrid())=='i') 
                    (yyval) = 1; 
                else if(gettype(getcurrid())=='f') 
                    (yyval)=2; 
                else 
                    (yyval)=-1;

                if(!ck_symbol_table())
                {
                    printf("ERROR:undeclared variable\n");
                }
                }
#line 2001 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2005 "y.tab.c" /* yacc.c:1646  */
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
#line 472 "parser.yacc" /* yacc.c:1906  */


int yyerror()
{
    flag = 1;
    printf("PARSING ERROR at Line Number - %d\n",lineno);
    return (1);
}

int main()
{
	
	
    yyin=fopen("test.txt","r");


    yyparse();

    if(comment_nesting!=0)
        printf("LEXICAL ERROR : Unterminated Comment\n");

    printf("\n*****Symbol Table******\n\n");
    int i;
	for(i=0;i<1000;i++)
	{
		if(symbol_table[i].name[0]!='\0')
		{
			printf("Var:%s Type:%s Size:%d Scope:%d  Isfunction:%d args:%d\n",symbol_table[i].name,symbol_table[i].type,symbol_table[i].storage,symbol_table[i].scope,symbol_table[i].fundef,symbol_table[i].countargs);
		}
	}


	printf("\n*****Constant Table******\n\n");
	for(i=0;i<1000;i++)
	{
		if(constant_table[i].name[0]!='\0')
		{
			printf("%s	%s\n",constant_table[i].name,constant_table[i].type);
		}
	}

    if(!flag)
    {
        printf("\nParsing SUCCESSFUL.\n");
    }
}

char* getcurrid()
{
    return currid;
}

char* getcurrtype()
{
    return currtype;
}

char* getprevid()
{
    return previd;
}

char* getprevtype()
{
    return prevtype;
}

char gettype(char *name)
{
    int i;
    char t;
    int scp=-1;
	for (i=0;i<1001;i++){
		if(strcmp(symbol_table[i].name,name) == 0 && symbol_table[i].scope >scp){
			t =  (symbol_table[i].type[0]);
            scp=symbol_table[i].scope;
		}
	}
    return t;
}
