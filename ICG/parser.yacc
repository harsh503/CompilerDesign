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
    : DECLARATION_SPECIFIER FUNDECID FND_OPN {printf("%s:\n",fnname);} FUNDEF_CONTD  {printf("return default\n");}  {sym_update_fundef();fncount=0;fnlist[0]='\0';}
    ;

FUNDEF_CONTD
	:	FND_CLS COMPOUND_STATEMENT
	|	DEFINITION_SPECIFIER_LIST FND_CLS COMPOUND_STATEMENT
	;
FND_OPN
    : '(' {scope++;}
    ;

FND_CLS
    : ')' {scope--;}
    ;

DEFINITION_SPECIFIER_LIST
    :VARIABLE_DECLARATION  {fnlist[fncount++]=getcurrtype()[0];fnlist[fncount]='\0';if(getcurrtype()[0]=='v'){printf("ERROR:function argument cannot be void.\n");}}
    | DEFINITION_SPECIFIER_LIST ',' VARIABLE_DECLARATION {fnlist[fncount++]=getcurrtype()[0];fnlist[fncount]='\0';if(getcurrtype()[0]=='v'){printf("ERROR:function argument cannot be void.\n");}}
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
    | EXPID {push(getcurrid());} '=' {push("=");} EXPRESSION {codegenassign();if($5==1 && $1==$5)$$=1; else if($5==2 && $1==$5)$$=2; else $$=-1;}
    | EXPRESSION EQU_OP {push(yytext);} EXPRESSION {if($1==1 && $4==1)$$=1; else if($1==2 && $4==2)$$=2; else $$=-1; codegen();}
    | EXPRESSION REL_OP {push(yytext);} EXPRESSION {if($1==1 && $4==1)$$=1; else if($1==2 && $4==2)$$=2; else $$=-1;codegen();}
    | EXPRESSION ADD_OP {push(yytext);} EXPRESSION {if($1==1 && $4==1)$$=1; else if($1==2 && $4==2)$$=2; else $$=-1;codegen();}
    | EXPRESSION MUL_OP {push(yytext);} EXPRESSION {if($1==1 && $4==1)$$=1; else if($1==2 && $4==2)$$=2; else $$=-1;codegen();}
    | EXPRESSION LAND {push(yytext);} EXPRESSION {if($1==1 && $4==1)$$=1; else if($1==2 && $4==2)$$=2; else $$=-1;codegen();}
    | EXPRESSION LOR {push(yytext);} EXPRESSION {if($1==1 && $4==1)$$=1; else if($1==2 && $4==2)$$=2; else $$=-1;codegen();}
    | EXPRESSION BOR {push(yytext);} EXPRESSION {if($1==1 && $4==1)$$=1; else if($1==2 && $4==2)$$=2; else $$=-1;codegen();}
    | EXPRESSION BAND {push(yytext);} EXPRESSION {if($1==1 && $4==1)$$=1; else if($1==2 && $4==2)$$=2; else $$=-1;codegen();}
    | EXPRESSION BXOR {push(yytext);} EXPRESSION {if($1==1 && $4==1)$$=1; else if($1==2 && $4==2)$$=2; else $$=-1;codegen();}
    | NOT_OP EXPRESSION {if($2==1)$$=1; else if($2==2)$$=2; else $$=-1;}
    | INCDEC_OP {push(yytext);} EXPID {if($3==1)$$ = 1; else $$ = -1;push(yytext);genunary();$$=$2;genunary();}
    | EXPID INCDEC_OP {push(yytext);$$=$1;genunary();}
    | '(' EXPRESSION ')' {$$=$2;}
    | EXPID  {push(getcurrid());$$=$1;}
    | INTVALUE {push(yycons); insert_constant_table(); $$=1;}
    | FLOATVALUE {push(yycons); insert_constant_table(); $$=2;}
    | FUNCTION_CALL {$$ = $1; if($1==-1)$$=3;}
    | STRING_LITERAL {insert_constant_table_str(); $$=-1;}
    ; 

FUNCTION_CALL
    : EXPID FNC_OPN  FUNCTION_CALL_CONTD  {$$=$1;if(!sym_ck_funcall()){printf("Error:function defination does not match any existing function definations\n");}fnccount=0;fnclist[0]='\0';;printf("call: %s\n",fncname);} 
    ;
FNC_OPN
    : '('   {copyfncname();}
    ;
FUNCTION_CALL_CONTD
    : ')' 
    |  EXPRESSION_LIST ')' 
    ;
EXPRESSION_LIST
    : EXPRESSION_LIST ',' EXPRESSION {printf("ref %s\n",s[top].value);} {if($3==-1) printf("Invalid Expression\n");else if($3==1){fnclist[fnccount++]='i';fnclist[fnccount]='\0';}else if($3==2){fnclist[fnccount++]='f';fnclist[fnccount]='\0';}}
    | EXPRESSION {printf("ref %s\n",s[top].value);}{if($1==-1) printf("Invalid Expression\n");else if($1==1){fnclist[fnccount++]='i';fnclist[fnccount]='\0';}else if($1==2){fnclist[fnccount++]='f';fnclist[fnccount]='\0';}}
    ;



SELECTION_STATEMENT 
    : IF '(' EXPRESSION {label1();} ')' STATEMENT {label2();} IF_CONTD     {if($3==-1) printf("Invalid Expression\n");}
    | SWITCH '(' EXPRESSION ')' STATEMENT {if($3==-1) printf("Invalid Expression\n");}
    ;

IF_CONTD
    : %prec LOWER_THAN_ELSE {label3();}
    |   ELSE  STATEMENT {label3();}
    ;

ITERATION_STATEMENT
    :  WHILE {label4();} '(' EXPRESSION ')' {label1();} STATEMENT { label5(); if($4==-1) printf("Invalid Expression\n");else if($4!=1){printf("While should have a interger expression\n");}}
    | DO {label4();} STATEMENT WHILE '(' EXPRESSION ')' {label1();} ';' { label5();if($5==-1) printf("Invalid Expression\n");}
    | FOR '(' EXPRESSION_STATEMENT ACTION1 EXPRESSION_STATEMENT ACTION2 ')' STATEMENT {label6();}
    | FOR '(' EXPRESSION_STATEMENT ACTION1 EXPRESSION_STATEMENT ACTION2 EXPRESSION ')' STATEMENT {label6(); if($5==-1) printf("Invalid Expression\n");}
    ;

ACTION1
    : {label4();}
    ;

ACTION2
    : {label1();}
    ;

JUMP_STATEMENT
    : CONTINUE ';'
    | BREAK ';'
    | RETURN ';'    {printf("return\n");}{if(gettype(fnname)!='v'){printf("Error Return type wrong.\n");}}
    | RETURN EXPRESSION {printf("return %s\n",s[top].value);}{if($2==-1) printf("Invalid Expression\n");else if(($2==1&& gettype(fnname)!='i') || ($2==2 && gettype(fnname)!='f') ){printf("Error Return type wrong.\n");}}
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
	:IDENTIFIER {isfunction=1;copyfnname();insert_symbol_table();isfunction=0;}
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
