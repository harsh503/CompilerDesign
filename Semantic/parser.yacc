%token AUTO BREAK CASE CHAR CONTINUE DEFAULT DO DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INT LONG REGISTER RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE
%token IDENTIFIER STRING_LITERAL ASSIGN_OP REL_OP ADD_OP MUL_OP INCDEC_OP EQU_OP  LAND LOR BAND BXOR BOR NOT_OP
%token INTVALUE FLOATVALUE
%expect 2

%{


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
            char* tmp = getcurrtype();
            strcpy(temp.type,tmp);
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

%}

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%right ASSIGN_OP '='
%left LOR
%left LAND
%left BOR
%left BXOR
%left BAND
%left EQU_OP 
%left REL_OP 
%left ADD_OP 
%left MUL_OP 
%right NOT_OP
%left INCDEC_OP  

%start PROGRAM

%%

PROGRAM 
    :EXTERNAL_DECLARATION
    |PROGRAM EXTERNAL_DECLARATION
    ;

EXTERNAL_DECLARATION
    :FUNCTION_DEFINITION
    |DECLARATION
    ;

DECLARATION 
    : DECLARATION_SPECIFIER INIT_DECLARATOR_LIST ';'
    ;

DECLARATION_SPECIFIER
    : TYPE_SPECIFIER 
    ;

TYPE_SPECIFIER
    : VOID
    | INT
    | FLOAT
    ;

INIT_DECLARATOR_LIST 
    : INIT_DECLARATOR
    | INIT_DECLARATOR_LIST ',' INIT_DECLARATOR
    ;

INIT_DECLARATOR
    : DECLARATOR
    | DECLARATOR '=' EXPRESSION {if($3==-1) printf("Invalid Expression\n");}
    ;   

DECLARATOR
    : DECID 
    | '(' DECLARATOR ')'
    ;

FUNCTION_DEFINITION 
    : DECLARATION_SPECIFIER FUNDECID '('  ')' COMPOUND_STATEMENT 
    | DECLARATION_SPECIFIER FUNDECID '(' DEFINITION_SPECIFIER_LIST ')' COMPOUND_STATEMENT 
    ;

DEFINITION_SPECIFIER_LIST
    :VARIABLE_DECLARATION 
    | DEFINITION_SPECIFIER_LIST ',' VARIABLE_DECLARATION
    ;
VARIABLE_DECLARATION
    :DECLARATION_SPECIFIER IDENTIFIER {insert_symbol_table();}
    ;
COMPOUND_STATEMENT
    :OP_BRACE  STATEMENT_LIST CL_BRACE
    |OP_BRACE CL_BRACE
    ;

STATEMENT_LIST
    :STATEMENT_LIST STATEMENT
    |STATEMENT
    ;



STATEMENT
    : LABELED_STATEMENT
    | COMPOUND_STATEMENT
    | EXPRESSION_STATEMENT
    | ITERATION_STATEMENT
    | SELECTION_STATEMENT
    | JUMP_STATEMENT
    | DECLARATION
    | error ';'
    ;



LABELED_STATEMENT
    : CASE EXPRESSION ':' STATEMENT {if($2==-1) printf("Invalid Expression\n");}
    | DEFAULT ':' STATEMENT
    ;

EXPRESSION_STATEMENT
    : ';'
    | EXPRESSION ';' {if($1==-1) printf("Invalid Expression\n");}
    ;

EXPRESSION
    : EXPID ASSIGN_OP EXPRESSION { if($3==1 && $1==$3)$$=1; else if($3==2 && $1==$3)$$=2; else $$=-1;}
    | EXPID '=' EXPRESSION {if($3==1 && $1==$3)$$=1; else if($3==2 && $1==$3)$$=2; else $$=-1;}
    | EXPRESSION EQU_OP EXPRESSION {if($1==1 && $3==1)$$=1; else if($1==2 && $3==2)$$=2; else $$=-1;}
    | EXPRESSION REL_OP EXPRESSION {printf("chk%d\n",$1); if($1==1 && $3==1)$$=1; else if($1==2 && $3==2)$$=2; else $$=-1;}
    | EXPRESSION ADD_OP EXPRESSION {if($1==1 && $3==1)$$=1; else if($1==2 && $3==2)$$=2; else $$=-1;}
    | EXPRESSION MUL_OP EXPRESSION {if($1==1 && $3==1)$$=1; else if($1==2 && $3==2)$$=2; else $$=-1;}
    | EXPRESSION LAND EXPRESSION {if($1==1 && $3==1)$$=1; else if($1==2 && $3==2)$$=2; else $$=-1;}
    | EXPRESSION LOR EXPRESSION {if($1==1 && $3==1)$$=1; else if($1==2 && $3==2)$$=2; else $$=-1;}
    | EXPRESSION BOR EXPRESSION {if($1==1 && $3==1)$$=1; else if($1==2 && $3==2)$$=2; else $$=-1;}
    | EXPRESSION BAND EXPRESSION {if($1==1 && $3==1)$$=1; else if($1==2 && $3==2)$$=2; else $$=-1;}
    | EXPRESSION BXOR EXPRESSION {if($1==1 && $3==1)$$=1; else if($1==2 && $3==2)$$=2; else $$=-1;}
    | NOT_OP EXPRESSION {if($2==1)$$=1; else if($2==2)$$=2; else $$=-1;}
    | INCDEC_OP EXPID {$$=$2;}
    | EXPID INCDEC_OP {$$=$1;}
    | '(' EXPRESSION ')' {if($2==1)$$=1; else $$=-1;}
    | EXPID  {$$=$1;}
    | INTVALUE {insert_constant_table(); $$=1;}
    | FLOATVALUE {insert_constant_table(); $$=2;}
    | FUNCTION_CALL {$$ = 1; }
    | STRING_LITERAL {insert_constant_table_str(); $$=-1;}
    ; 

FUNCTION_CALL
    : EXPID '(' ')' 
    | EXPID '(' EXPRESSION_LIST ')'      
    ;

EXPRESSION_LIST
    : EXPRESSION_LIST ',' EXPRESSION {if($3==-1) printf("Invalid Expression\n");}
    | EXPRESSION {if($1==-1) printf("Invalid Expression\n");}
    ;



SELECTION_STATEMENT 
    : IF '(' EXPRESSION ')' STATEMENT  %prec LOWER_THAN_ELSE {if($3==-1) printf("Invalid Expression\n");}
    | IF '(' EXPRESSION ')' STATEMENT ELSE STATEMENT {if($3==-1) printf("Invalid Expression\n");}
    | SWITCH '(' EXPRESSION ')' STATEMENT {if($3==-1) printf("Invalid Expression\n");}
    ;



ITERATION_STATEMENT
    : WHILE '(' EXPRESSION ')' STATEMENT { printf("val%d\n",$3);if($3==-1) printf("Invalid Expression\n");}
    | DO STATEMENT WHILE '(' EXPRESSION ')' ';' {if($5==-1) printf("Invalid Expression\n");}
    | FOR '(' EXPRESSION_STATEMENT EXPRESSION_STATEMENT ')' STATEMENT
    | FOR '(' EXPRESSION_STATEMENT EXPRESSION_STATEMENT EXPRESSION ')' STATEMENT {if($5==-1) printf("Invalid Expression\n");}
    ;

JUMP_STATEMENT
    : CONTINUE ';'
    | BREAK ';'
    | RETURN ';'
    | RETURN EXPRESSION {if($2==-1) printf("Invalid Expression\n");}
    ;

OP_BRACE
	:'{' {scope++;}
	;

CL_BRACE
	:'}' {delete_sym(scope);scope--;}
	;


DECID
	:IDENTIFIER {insert_symbol_table();}
	;

FUNDECID
	:IDENTIFIER {isfunction=1;insert_symbol_table();isfunction=0;}
	;
EXPID
	:IDENTIFIER {

                if(gettype(getcurrid())=='i') 
                    $$ = 1; 
                else if(gettype(getcurrid())=='f') 
                    $$=2; 
                else 
                    $$=-1;

                if(!ck_symbol_table())
                {
                    printf("ERROR:undeclared variable\n");
                }
                }
	;




%%

int yyerror()
{
    flag = 1;
    printf("PARSING ERROR at Line Number - %d\n",lineno);
    return (1);
}

main()
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
			printf("%s	%s %d \n",symbol_table[i].name,symbol_table[i].type,symbol_table[i].scope);
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
	for (i=0;i<1001;i++){
		if(strcmp(symbol_table[i].name,name) == 0 && symbol_table[i].scope <= scope){
			t =  (symbol_table[i].type[0]);
		}
	}
    return t;
}