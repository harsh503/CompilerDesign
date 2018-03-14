%token AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INT LONG REGISTER RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE
%token IDENTIFIER CONSTANT STRING_LITERAL ASSIGN_OP REL_OP ADD_OP MUL_OP INCDEC_OP EQU_OP  LAND LOR BAND BXOR BOR NOT_OP
%expect 2

%{


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

extern FILE *yyin;
extern int lineno;
extern int comment_nesting;
int scope=0;
//Stack

struct Stack
{
    int top;
    unsigned capacity;
    int* array;
};
struct Stack* stack; 
// function to create a stack of given capacity. It initializes size of
// stack as 0
struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*) malloc(stack->capacity * sizeof(int));
    return stack;
}
 
// Stack is full when top is equal to the last index
int isFull(struct Stack* stack)
{   return stack->top == stack->capacity - 1; }
 
// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack)
{   return stack->top == -1;  }
 
// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}
 
// Function to remove an item from stack.  It decreases top by 1
int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];

}


int flag = 0;
int errorFlag=0;
struct stable{
	char name[100];
	char type[50];
	long long int scope;
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
	void insert_symbol_table()
	{
	    int k=hash_cal(yyval);
			struct stable temp;
			strcpy(temp.name,yyval);
			strcpy(temp.type,"identifier");
			int tempscope=pop(stack);
			push(stack,tempscope);
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
						printf();
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
    : STORAGE_CLASS_SPECIFIER 
    | STORAGE_CLASS_SPECIFIER DECLARATION_SPECIFIER 
    | TYPE_SPECIFIER 
    | TYPE_SPECIFIER DECLARATION_SPECIFIER
    ;

STORAGE_CLASS_SPECIFIER
    : TYPEDEF
    | EXTERN
    | STATIC
    | AUTO
    | REGISTER
    ;

TYPE_SPECIFIER
    : VOID
    | CHAR
    | SHORT
    | INT
    | LONG
    | FLOAT
    | DOUBLE
    | SIGNED
    | UNSIGNED
    ;

INIT_DECLARATOR_LIST 
    : INIT_DECLARATOR
    | INIT_DECLARATOR_LIST ',' INIT_DECLARATOR
    ;

INIT_DECLARATOR
    : DECLARATOR
    | DECLARATOR '=' EXPRESSION
    | DECLARATOR '=' STRING_LITERAL {insert_constant_table_str();}
    ;   

DECLARATOR
    : DECID 
    | '(' DECLARATOR ')'
    | DECLARATOR '[' CONSTANT ']' {insert_constant_table();}
    | DECLARATOR '[' ']'
    | FUNCTION_DECLARATION
    ;

FUNCTION_DECLARATION
    : FUNDECID '(' DECLARATION_SPECIFIER_LIST ')'  
    | FUNDECID '(' ')' 
    ;

FUNCTION_DEFINITION 
    : DECLARATION_SPECIFIER FUNDECID '('  ')' COMPOUND_STATEMENT 
    | DECLARATION_SPECIFIER FUNDECID '(' DEFINITION_SPECIFIER_LIST ')' COMPOUND_STATEMENT 
    ;


DECLARATION_SPECIFIER_LIST
    : DECLARATION_SPECIFIER_LIST ',' DECLARATION_SPECIFIER 
    | DECLARATION_SPECIFIER
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
    : CASE EXPRESSION ':' STATEMENT
    | DEFAULT ':' STATEMENT
    ;

EXPRESSION_STATEMENT
    : ';'
    | EXPRESSION ';'
    ;

EXPRESSION
    : EXPID ASSIGN_OP EXPRESSION 
    | EXPID '=' EXPRESSION 
    | EXPRESSION EQU_OP EXPRESSION
    | EXPRESSION REL_OP EXPRESSION
    | EXPRESSION ADD_OP EXPRESSION
    | EXPRESSION MUL_OP EXPRESSION
    | EXPRESSION LAND EXPRESSION
    | EXPRESSION LOR EXPRESSION
    | EXPRESSION BOR EXPRESSION
    | EXPRESSION BAND EXPRESSION
    | EXPRESSION BXOR EXPRESSION
    | NOT_OP EXPRESSION 
    | INCDEC_OP EXPID
    | EXPID INCDEC_OP
    | '(' EXPRESSION ')'
    | EXPID  
    | CONSTANT {insert_constant_table();}
    | FUNCTION_CALL
    ; 

FUNCTION_CALL
    : EXPID '(' ')' 
    | EXPID '(' EXPRESSION_LIST ')'      
    ;

EXPRESSION_LIST
    : EXPRESSION_LIST ',' EXPRESSION
    | EXPRESSION
    ;



SELECTION_STATEMENT 
    : IF '(' EXPRESSION ')' STATEMENT  %prec LOWER_THAN_ELSE 
    | IF '(' EXPRESSION ')' STATEMENT ELSE STATEMENT 
    | SWITCH '(' EXPRESSION ')' STATEMENT
    ;



ITERATION_STATEMENT
    : WHILE '(' EXPRESSION ')' STATEMENT
    | DO STATEMENT WHILE '(' EXPRESSION ')' ';'
    | FOR '(' EXPRESSION_STATEMENT EXPRESSION_STATEMENT ')' STATEMENT
    | FOR '(' EXPRESSION_STATEMENT EXPRESSION_STATEMENT EXPRESSION ')' STATEMENT
    ;

JUMP_STATEMENT
    : CONTINUE ';'
    | BREAK ';'
    | RETURN ';'
    | RETURN EXPRESSION 
    ;

OP_BRACE
	:'{' {scope++;push(stack,scope);}
	;

CL_BRACE
	:'}' {pop(stack);}
	;


DECID
	:IDENTIFIER {insert_symbol_table();}
	;

FUNDECID
	:IDENTIFIER {insert_symbol_table();}
	;
EXPID
	:IDENTIFIER
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
	
	stack = createStack(100);
	push(stack,scope);
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
