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
extern char * yytext;
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
                //printf("ENTRY DELETED::%s   %s  %d \n",symbol_table[i].name,symbol_table[i].type,symbol_table[i].scope);
                symbol_table[i].name[0]='\0';
                symbol_table[i].type[0]!='\0';

            }
        }
    }
// ICG CODE Starts Here
 int top = 0, lno=1, label[20], ltop=0, cnt=0;
    char st[100][10], temp[3] = "t", zz[6];

    struct Stack
{
    char value[100];
}s[100];

void convert(int x)
{
    if(x==0){
        strcpy(zz,"0");
		return ;
    }
    int dig=0;
    int tmp=x;
    while(tmp){
        dig++;
        tmp/=10;
    }

    char res[6];
    tmp=x;
    res[dig]='\0';
    dig--;
    while(tmp){
        int a=tmp%10;
        res[dig]='0'+a;
        tmp/=10;
        dig--;
    }
    strcpy(zz, res);
    //return res;
}

void label1()
{
    strcpy(temp,"t");
    convert(cnt);
    strcat(temp, zz);
    printf("%s = not %s\n",temp,s[top].value);
    printf("if %s goto L%d\n",temp,lno);
    cnt++;
    label[++ltop]=lno++;
}    

void label2()
{
    printf("goto L%d\n",lno);
    printf("L%d:\n",label[ltop]);
    ltop--;
    label[++ltop]=lno++;
}

void label3()
{
    printf("L%d: \n", label[ltop--]);
}

void label4()
{
    printf("L%d: \n",lno);
    label[++ltop]=lno++;
}

void label5()
{
    printf("goto L%d \n",label[ltop-1]);
    printf("L%d: \n",label[ltop]);
    ltop -= 2;
}

void label6()
{
    printf("goto L%d \n",label[ltop-1]);
    printf("L%d: \n",label[ltop]);
    ltop -= 2;
}

void push(char* item)
{
    strcpy(s[++top].value, item);
}

void codegenassign()
{
    printf("%s = %s\n", s[top-2].value, s[top].value);
    top-=2;
}

int isunary(char *s){
    if(strcmp(s,"-")==0)
    return 1;

    if(strcmp(s,"++")==0)
    return 1;

    if(strcmp(s,"--")==0)
    return 1;
    return 0;
}

void genunary(){
    char tmp1[102],tmp2[102],tmp3[102];
    strcpy(tmp1,s[top].value);
    strcpy(tmp2,s[top-1].value);
    if(isunary(tmp1)){
        strcpy(tmp3,tmp1);
        strcpy(tmp1,tmp2);
        strcpy(tmp2,tmp3);
    }

    strcpy(temp,"t");
    convert(cnt);
    strcat(temp,zz);
    cnt++;

    if(strcmp(tmp2,"--")==0){
        printf("%s = %s - 1\n",temp,tmp1);
        printf("%s = %s\n",tmp1,temp);
    }

    if(strcmp(tmp2,"++")==0){
        printf("%s = %s + 1\n",temp,tmp1);
        printf("%s = %s\n",tmp1,temp);
    }
    
    if(strcmp(tmp2,"-")==0){
        printf("%s = -%s \n",temp,tmp1);
     //   printf("%s = %s\n",tmp1,temp);
    }
    top-=2;
    push(temp);
}

void codegen()
{
    strcpy(temp, "t");
	convert(cnt);
    strcat(temp, zz);
    printf("%s = %s %s %s\n", temp, s[top-2].value, s[top-1].value, s[top].value);
    top-=2;
    strcpy(s[top].value, temp);
    cnt++;
}



#line 468 "y.tab.c" /* yacc.c:339  */

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



/* Copy the second part of user declarations.  */

#line 616 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   370

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  174

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
       0,   429,   429,   430,   434,   435,   439,   443,   447,   448,
     449,   453,   454,   458,   459,   463,   464,   468,   469,   473,
     477,   481,   482,   485,   488,   489,   493,   494,   500,   501,
     502,   503,   504,   505,   506,   507,   513,   514,   518,   519,
     523,   524,   524,   524,   525,   525,   526,   526,   527,   527,
     528,   528,   529,   529,   530,   530,   531,   531,   532,   532,
     533,   533,   534,   535,   535,   536,   537,   538,   539,   540,
     541,   542,   546,   549,   552,   553,   556,   557,   563,   563,
     563,   564,   568,   569,   573,   573,   573,   574,   574,   574,
     575,   576,   580,   584,   588,   589,   590,   591,   595,   599,
     604,   608,   611
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
  "EXPRESSION_STATEMENT", "EXPRESSION", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "@12", "FUNCTION_CALL",
  "FNC_OPN", "FUNCTION_CALL_CONTD", "EXPRESSION_LIST",
  "SELECTION_STATEMENT", "$@13", "$@14", "IF_CONTD", "ITERATION_STATEMENT",
  "$@15", "$@16", "$@17", "$@18", "ACTION1", "ACTION2", "JUMP_STATEMENT",
  "OP_BRACE", "CL_BRACE", "DECID", "FUNDECID", "EXPID", YY_NULLPTR
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

#define YYPACT_NINF -112

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-112)))

#define YYTABLE_NINF -102

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      24,  -112,  -112,  -112,     4,  -112,  -112,   -25,  -112,  -112,
    -112,  -112,   -47,   -20,   -40,  -112,   -28,  -112,   -29,  -112,
     -27,  -112,   -20,   186,  -112,     2,  -112,  -112,  -112,  -112,
    -112,   186,  -112,  -112,   186,   287,  -112,   -30,  -112,     6,
     -13,   -14,  -112,    33,  -112,   200,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,   186,  -112,  -112,     5,   128,
    -112,  -112,  -112,    84,    24,   -13,  -112,  -112,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   287,  -112,  -112,
     287,  -112,    55,    26,    43,   186,    51,    18,  -112,    36,
      46,   160,    50,  -112,  -112,  -112,  -112,   -20,  -112,    84,
    -112,  -112,  -112,   275,  -112,  -112,  -112,  -112,  -112,  -112,
      48,    68,  -112,    32,   307,   297,    22,   326,   317,   186,
     186,  -112,  -112,  -112,    38,  -112,   139,   139,   176,   186,
    -112,   287,   186,    58,  -112,  -112,  -112,   287,   287,   139,
    -112,    80,  -112,   287,   215,   186,  -112,    60,   176,    61,
     139,   230,   186,  -112,   139,  -112,  -112,   245,   150,  -112,
     139,  -112,   139,   260,   109,  -112,    69,  -112,   139,   139,
    -112,  -112,  -112,  -112
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    10,     9,     8,     0,     2,     5,     0,     7,     4,
       1,     3,   100,     0,     0,    11,    13,    15,     0,   100,
       0,     6,     0,     0,    19,     0,    16,    12,   102,    71,
      63,     0,    68,    69,     0,    14,    70,    67,    20,     0,
       0,     0,    21,     0,    62,     0,    46,    48,    50,    44,
      52,    54,    58,    60,    56,     0,    65,    73,     0,     0,
      23,    98,    17,     0,     0,     0,    64,    66,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    40,    42,    74,
      77,    72,     0,     0,     0,     0,     0,     0,    87,     0,
       0,     0,     0,    84,    38,    99,    34,     0,    29,     0,
      27,    28,    30,     0,    32,    31,    33,    25,    22,    18,
      47,    49,    51,    45,    53,    55,    59,    61,    57,     0,
       0,    75,    35,    95,     0,    94,     0,     0,     0,     0,
      96,    97,     0,     0,    26,    24,    39,    43,    76,     0,
      37,     0,    92,    78,     0,     0,    36,     0,     0,     0,
       0,     0,     0,    93,     0,    81,    85,     0,     0,    79,
       0,    88,     0,     0,    82,    86,     0,    90,     0,     0,
      80,    89,    91,    83
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -112,  -112,   119,    15,     1,  -112,  -112,   103,   113,  -112,
    -112,    86,  -112,    64,   -38,  -112,   -96,  -112,  -111,   -23,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,    31,
    -112,  -112,    91
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,    96,    97,     8,    14,    15,    16,     9,
      25,    40,    41,    42,    98,    99,   100,   101,   102,   103,
      58,   119,    71,    68,    69,    70,    72,    73,    76,    74,
      75,    43,    36,    59,    81,    82,   104,   149,   164,   170,
     105,   133,   160,   127,   166,   148,   158,   106,    63,   107,
      17,    18,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,     7,    62,   134,    10,     7,    55,  -101,    44,    12,
      56,    45,    21,    22,    19,     6,     1,   142,     1,     6,
       2,   -41,     2,    23,    57,    24,    39,   109,    26,    13,
     140,   141,    77,     3,    13,     3,    80,   153,     1,    64,
      60,    38,     2,   146,    61,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   155,     3,    78,    38,   159,    46,
      47,    48,   124,    49,   165,    39,   167,    28,   131,    46,
      47,    48,   172,   173,   126,    46,    47,    48,   122,    49,
      50,    51,    52,    53,    54,    83,    47,    48,    84,    85,
     128,    86,    87,    88,   139,   123,   137,   138,     1,    89,
     129,    90,     2,   125,   132,    91,   143,    48,   120,   144,
     121,    92,   145,   147,   152,     3,   154,    93,    28,    29,
     169,   171,   151,    11,    30,    27,    20,    65,   108,   157,
     135,    31,    32,    33,    66,   163,    94,     0,    34,     0,
      83,    61,    95,    84,    85,     0,    86,    87,    88,     0,
       0,     0,     0,     1,    89,     0,    90,     2,     0,     0,
      91,     0,    28,    29,     0,     0,    92,     0,    30,     0,
       3,     0,    93,    28,    29,    31,    32,    33,     0,    30,
       0,     0,    34,    79,    28,    29,    31,    32,    33,     0,
      30,    94,     0,    34,    28,    29,    61,    31,    32,    33,
      30,     0,     0,     0,    34,   162,     0,    31,    32,    33,
      28,    29,   130,     0,    34,     0,    30,     0,     0,     0,
      28,    29,     0,    31,    32,    33,    30,     0,    94,     0,
      34,     0,     0,    31,    32,    33,     0,    46,    47,    48,
      34,    49,    50,    51,    52,    53,    54,     0,     0,     0,
       0,     0,    46,    47,    48,    67,    49,    50,    51,    52,
      53,    54,     0,     0,     0,     0,     0,    46,    47,    48,
     150,    49,    50,    51,    52,    53,    54,     0,     0,     0,
       0,     0,    46,    47,    48,   156,    49,    50,    51,    52,
      53,    54,     0,     0,     0,     0,     0,    46,    47,    48,
     161,    49,    50,    51,    52,    53,    54,     0,     0,     0,
       0,     0,    46,    47,    48,   168,    49,    50,    51,    52,
      53,    54,     0,     0,    46,    47,    48,   136,    49,    50,
      51,    52,    53,    54,    46,    47,    48,     0,    49,    50,
       0,    52,    53,    54,    46,    47,    48,     0,    49,     0,
       0,    52,    53,    54,    46,    47,    48,     0,    49,     0,
       0,    52,    53,    46,    47,    48,     0,    49,     0,     0,
      52
};

static const yytype_int16 yycheck[] =
{
      23,     0,    40,    99,     0,     4,    36,    54,    31,    34,
      40,    34,    52,    53,    34,     0,    14,   128,    14,     4,
      18,    51,    18,    51,    54,    54,    25,    65,    55,    54,
     126,   127,    55,    31,    54,    31,    59,   148,    14,    53,
      34,    55,    18,   139,    57,    68,    69,    70,    71,    72,
      73,    74,    75,    76,   150,    31,    51,    55,   154,    37,
      38,    39,    85,    41,   160,    64,   162,    34,    91,    37,
      38,    39,   168,   169,    56,    37,    38,    39,    52,    41,
      42,    43,    44,    45,    46,     1,    38,    39,     4,     5,
      54,     7,     8,     9,    56,    52,   119,   120,    14,    15,
      54,    17,    18,    52,    54,    21,   129,    39,    53,   132,
      55,    27,    54,    33,    54,    31,    55,    33,    34,    35,
      11,    52,   145,     4,    40,    22,    13,    41,    64,   152,
      99,    47,    48,    49,    43,   158,    52,    -1,    54,    -1,
       1,    57,    58,     4,     5,    -1,     7,     8,     9,    -1,
      -1,    -1,    -1,    14,    15,    -1,    17,    18,    -1,    -1,
      21,    -1,    34,    35,    -1,    -1,    27,    -1,    40,    -1,
      31,    -1,    33,    34,    35,    47,    48,    49,    -1,    40,
      -1,    -1,    54,    55,    34,    35,    47,    48,    49,    -1,
      40,    52,    -1,    54,    34,    35,    57,    47,    48,    49,
      40,    -1,    -1,    -1,    54,    55,    -1,    47,    48,    49,
      34,    35,    52,    -1,    54,    -1,    40,    -1,    -1,    -1,
      34,    35,    -1,    47,    48,    49,    40,    -1,    52,    -1,
      54,    -1,    -1,    47,    48,    49,    -1,    37,    38,    39,
      54,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    55,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      55,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    55,    41,    42,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,
      55,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    55,    41,    42,    43,    44,
      45,    46,    -1,    -1,    37,    38,    39,    52,    41,    42,
      43,    44,    45,    46,    37,    38,    39,    -1,    41,    42,
      -1,    44,    45,    46,    37,    38,    39,    -1,    41,    -1,
      -1,    44,    45,    46,    37,    38,    39,    -1,    41,    -1,
      -1,    44,    45,    37,    38,    39,    -1,    41,    -1,    -1,
      44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    18,    31,    60,    61,    62,    63,    64,    68,
       0,    61,    34,    54,    65,    66,    67,   109,   110,    34,
      67,    52,    53,    51,    54,    69,    55,    66,    34,    35,
      40,    47,    48,    49,    54,    78,    91,   111,    55,    63,
      70,    71,    72,    90,    78,    78,    37,    38,    39,    41,
      42,    43,    44,    45,    46,    36,    40,    54,    79,    92,
      34,    57,    73,   107,    53,    70,   111,    55,    82,    83,
      84,    81,    85,    86,    88,    89,    87,    78,    51,    55,
      78,    93,    94,     1,     4,     5,     7,     8,     9,    15,
      17,    21,    27,    33,    52,    58,    62,    63,    73,    74,
      75,    76,    77,    78,    95,    99,   106,   108,    72,    73,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    80,
      53,    55,    52,    52,    78,    52,    56,   102,    54,    54,
      52,    78,    54,   100,    75,   108,    52,    78,    78,    56,
      75,    75,    77,    78,    78,    54,    75,    33,   104,    96,
      55,    78,    54,    77,    55,    75,    55,    78,   105,    75,
     101,    55,    55,    78,    97,    75,   103,    75,    55,    11,
      98,    52,    75,    75
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    60,    61,    61,    62,    63,    64,    64,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      70,    71,    71,    72,    73,    73,    74,    74,    75,    75,
      75,    75,    75,    75,    75,    75,    76,    76,    77,    77,
      78,    79,    80,    78,    81,    78,    82,    78,    83,    78,
      84,    78,    85,    78,    86,    78,    87,    78,    88,    78,
      89,    78,    78,    90,    78,    78,    78,    78,    78,    78,
      78,    78,    91,    92,    93,    93,    94,    94,    96,    97,
      95,    95,    98,    98,   100,   101,    99,   102,   103,    99,
      99,    99,   104,   105,   106,   106,   106,   106,   107,   108,
     109,   110,   111
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     3,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     3,     5,     6,     1,
       1,     1,     3,     2,     3,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     4,     3,     1,     2,
       3,     0,     0,     5,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     2,     0,     3,     2,     3,     1,     1,     1,
       1,     1,     3,     1,     1,     2,     3,     1,     0,     0,
       8,     5,     0,     2,     0,     0,     7,     0,     0,     9,
       8,     9,     0,     0,     2,     2,     2,     2,     1,     1,
       1,     1,     1
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
#line 459 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[0])==-1) printf("Invalid Expression\n");}
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 468 "parser.yacc" /* yacc.c:1646  */
    {sym_update_fundef();fncount=0;fnlist[0]='\0';}
#line 1879 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 469 "parser.yacc" /* yacc.c:1646  */
    {sym_update_fundef();fncount=0;fnlist[0]='\0';}
#line 1885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 473 "parser.yacc" /* yacc.c:1646  */
    {scope++;}
#line 1891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 477 "parser.yacc" /* yacc.c:1646  */
    {scope--;}
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 481 "parser.yacc" /* yacc.c:1646  */
    {fnlist[fncount++]=getcurrtype()[0];fnlist[fncount]='\0';if(getcurrtype()[0]=='v'){printf("ERROR:function argument cannot be void.\n");}}
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 482 "parser.yacc" /* yacc.c:1646  */
    {fnlist[fncount++]=getcurrtype()[0];fnlist[fncount]='\0';if(getcurrtype()[0]=='v'){printf("ERROR:function argument cannot be void.\n");}}
#line 1909 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 485 "parser.yacc" /* yacc.c:1646  */
    {insert_symbol_table();}
#line 1915 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 513 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==-1) printf("Invalid Expression\n");}
#line 1921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 519 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-1])==-1) printf("Invalid Expression\n");}
#line 1927 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 523 "parser.yacc" /* yacc.c:1646  */
    { if((yyvsp[0])==1 && (yyvsp[-2])==(yyvsp[0]))(yyval)=1; else if((yyvsp[0])==2 && (yyvsp[-2])==(yyvsp[0]))(yyval)=2; else (yyval)=-1;}
#line 1933 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 524 "parser.yacc" /* yacc.c:1646  */
    {push(getcurrid());}
#line 1939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 524 "parser.yacc" /* yacc.c:1646  */
    {push("=");}
#line 1945 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 524 "parser.yacc" /* yacc.c:1646  */
    {codegenassign();if((yyvsp[0])==1 && (yyvsp[-4])==(yyvsp[0]))(yyval)=1; else if((yyvsp[0])==2 && (yyvsp[-4])==(yyvsp[0]))(yyval)=2; else (yyval)=-1;}
#line 1951 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 525 "parser.yacc" /* yacc.c:1646  */
    {push(yytext);}
#line 1957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 525 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-3])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-3])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1; codegen();}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 526 "parser.yacc" /* yacc.c:1646  */
    {push(yytext);}
#line 1969 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 526 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-3])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-3])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;codegen();}
#line 1975 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 527 "parser.yacc" /* yacc.c:1646  */
    {push(yytext);}
#line 1981 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 527 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-3])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-3])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;codegen();}
#line 1987 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 528 "parser.yacc" /* yacc.c:1646  */
    {push(yytext);}
#line 1993 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 528 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-3])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-3])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;codegen();}
#line 1999 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 529 "parser.yacc" /* yacc.c:1646  */
    {push(yytext);}
#line 2005 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 529 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-3])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-3])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;codegen();}
#line 2011 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 530 "parser.yacc" /* yacc.c:1646  */
    {push(yytext);}
#line 2017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 530 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-3])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-3])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;codegen();}
#line 2023 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 531 "parser.yacc" /* yacc.c:1646  */
    {push(yytext);}
#line 2029 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 531 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-3])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-3])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;codegen();}
#line 2035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 532 "parser.yacc" /* yacc.c:1646  */
    {push(yytext);}
#line 2041 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 532 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-3])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-3])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;codegen();}
#line 2047 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 533 "parser.yacc" /* yacc.c:1646  */
    {push(yytext);}
#line 2053 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 533 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-3])==1 && (yyvsp[0])==1)(yyval)=1; else if((yyvsp[-3])==2 && (yyvsp[0])==2)(yyval)=2; else (yyval)=-1;codegen();}
#line 2059 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 534 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[0])==1)(yyval)=1; else if((yyvsp[0])==2)(yyval)=2; else (yyval)=-1;}
#line 2065 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 535 "parser.yacc" /* yacc.c:1646  */
    {push(yytext);}
#line 2071 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 535 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[0])==1)(yyval) = 1; else (yyval) = -1;push(yytext);genunary();(yyval)=(yyvsp[-1]);genunary();}
#line 2077 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 536 "parser.yacc" /* yacc.c:1646  */
    {push(yytext);(yyval)=(yyvsp[-1]);genunary();}
#line 2083 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 537 "parser.yacc" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 2089 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 538 "parser.yacc" /* yacc.c:1646  */
    {push(getcurrid());(yyval)=(yyvsp[0]);}
#line 2095 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 539 "parser.yacc" /* yacc.c:1646  */
    {push(yycons); insert_constant_table(); (yyval)=1;}
#line 2101 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 540 "parser.yacc" /* yacc.c:1646  */
    {push(yycons); insert_constant_table(); (yyval)=2;}
#line 2107 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 541 "parser.yacc" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]); if((yyvsp[0])==-1)(yyval)=3;}
#line 2113 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 542 "parser.yacc" /* yacc.c:1646  */
    {insert_constant_table_str(); (yyval)=-1;}
#line 2119 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 546 "parser.yacc" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-2]);if(!sym_ck_funcall()){printf("Error:function defination does not match any existing function definations\n");}fnccount=0;fnclist[0]='\0';}
#line 2125 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 549 "parser.yacc" /* yacc.c:1646  */
    {copyfncname();}
#line 2131 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 556 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[0])==-1) printf("Invalid Expression\n");else if((yyvsp[0])==1){fnclist[fnccount++]='i';fnclist[fnccount]='\0';}else if((yyvsp[0])==2){fnclist[fnccount++]='f';fnclist[fnccount]='\0';}}
#line 2137 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 557 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[0])==-1) printf("Invalid Expression\n");else if((yyvsp[0])==1){fnclist[fnccount++]='i';fnclist[fnccount]='\0';}else if((yyvsp[0])==2){fnclist[fnccount++]='f';fnclist[fnccount]='\0';}}
#line 2143 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 563 "parser.yacc" /* yacc.c:1646  */
    {label1();}
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 563 "parser.yacc" /* yacc.c:1646  */
    {label2();}
#line 2155 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 563 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-5])==-1) printf("Invalid Expression\n");}
#line 2161 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 564 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[-2])==-1) printf("Invalid Expression\n");}
#line 2167 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 568 "parser.yacc" /* yacc.c:1646  */
    {label3();}
#line 2173 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 569 "parser.yacc" /* yacc.c:1646  */
    {label3();}
#line 2179 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 573 "parser.yacc" /* yacc.c:1646  */
    {label4();}
#line 2185 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 573 "parser.yacc" /* yacc.c:1646  */
    {label1();}
#line 2191 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 573 "parser.yacc" /* yacc.c:1646  */
    { label5(); if((yyvsp[-3])==-1) printf("Invalid Expression\n");else if((yyvsp[-3])!=1){printf("While should have a interger expression\n");}}
#line 2197 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 574 "parser.yacc" /* yacc.c:1646  */
    {label4();}
#line 2203 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 574 "parser.yacc" /* yacc.c:1646  */
    {label1();}
#line 2209 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 574 "parser.yacc" /* yacc.c:1646  */
    { label5();if((yyvsp[-4])==-1) printf("Invalid Expression\n");}
#line 2215 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 575 "parser.yacc" /* yacc.c:1646  */
    {label6();}
#line 2221 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 576 "parser.yacc" /* yacc.c:1646  */
    {label6(); if((yyvsp[-4])==-1) printf("Invalid Expression\n");}
#line 2227 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 580 "parser.yacc" /* yacc.c:1646  */
    {label4();}
#line 2233 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 584 "parser.yacc" /* yacc.c:1646  */
    {label1();}
#line 2239 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 590 "parser.yacc" /* yacc.c:1646  */
    {if(gettype(fnname)!='v'){printf("Error Return type wrong.\n");}}
#line 2245 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 591 "parser.yacc" /* yacc.c:1646  */
    {if((yyvsp[0])==-1) printf("Invalid Expression\n");else if(((yyvsp[0])==1&& gettype(fnname)!='i') || ((yyvsp[0])==2 && gettype(fnname)!='f') ){printf("Error Return type wrong.\n");}}
#line 2251 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 595 "parser.yacc" /* yacc.c:1646  */
    {scope++;}
#line 2257 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 599 "parser.yacc" /* yacc.c:1646  */
    {delete_sym(scope);scope--;}
#line 2263 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 604 "parser.yacc" /* yacc.c:1646  */
    {insert_symbol_table();}
#line 2269 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 608 "parser.yacc" /* yacc.c:1646  */
    {isfunction=1;copyfnname();insert_symbol_table();isfunction=0;}
#line 2275 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 611 "parser.yacc" /* yacc.c:1646  */
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
#line 2294 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2298 "y.tab.c" /* yacc.c:1646  */
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
#line 630 "parser.yacc" /* yacc.c:1906  */


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
    printf("Name\t\tType\t\tSize\t\tScope\t\tIsFunction\tNoOfArgs\n");
	for(i=0;i<1000;i++)
	{
		if(symbol_table[i].name[0]!='\0')
		{
			printf("%s\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d\n",symbol_table[i].name,symbol_table[i].type,symbol_table[i].storage,symbol_table[i].scope,symbol_table[i].fundef,symbol_table[i].countargs);
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
