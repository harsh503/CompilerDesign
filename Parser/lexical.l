%{
#include "y.tab.h"
#include<string.h>
#include<stdio.h>

int comment_nesting = 0; 
int lineno=1;

struct stable{
	char name[100];
	char type[50];
}symbol_table[1000];

struct ctable{
	char name[100];
	char type[50];
}constant_table[1000];

int hash_cal(char * str)
{
	int i;
	int sum=0;
	for(i=0;i<100;i++)
	{
		if(str[i]=='\0')
		{
			break;
		}
		else{
			sum+=(int)str[i];
			sum=sum%1000;
		}
	}
	return sum;
}

%}

IDENTIFIER [A-Za-z_]([A-Za-z_]|[0-9])*
notid [0-9]+([A-Za-z_]|[0-9])*
CONSTANT (([0-9])*)(\.(([0-9])+))?(([eE])([\+\-]?)(([0-9])+))?
ws " "|"	"|"\n"

%x SC_COMMENT

%%

"/*"             { comment_nesting++; BEGIN(SC_COMMENT); }
<SC_COMMENT>{
  "/*"           { comment_nesting++; }
  "*"+"/"        { comment_nesting=0;
                    BEGIN(INITIAL);  }
  "*"+           ;
  [^/*\n]+       ;
  [/]            ;
  \n             {lineno++;}
}

"auto"			{ return(AUTO); }
"break"			{ return(BREAK); }
"case"			{ return(CASE); }
"char"			{ return(CHAR); }
"const"			{ return(CONST); }
"continue"		{ return(CONTINUE); }
"default"		{ return(DEFAULT); }
"do"			{ return(DO); }
"double"		{ return(DOUBLE); }
"else"			{ return(ELSE); }
"enum"			{ return(ENUM); }
"extern"		{ return(EXTERN); }
"float"			{ return(FLOAT); }
"for"			{ return(FOR); }
"goto"			{ return(GOTO); }
"if"			{ return(IF); }
"int"			{ return(INT); }
"long"			{ return(LONG); }
"register"		{ return(REGISTER); }
"return"		{ return(RETURN); }
"short"			{ return(SHORT); }
"signed"		{ return(SIGNED); }
"sizeof"		{ return(SIZEOF); }
"static"		{ return(STATIC); }
"struct"		{ return(STRUCT); }
"switch"		{ return(SWITCH); }
"typedef"		{ return(TYPEDEF); }
"union"			{ return(UNION); }
"unsigned"		{ return(UNSIGNED); }
"void"			{ return(VOID); }
"volatile"		{ return(VOLATILE); }
"while"			{ return(WHILE); }

{IDENTIFIER} 	{	printf("%s - identifier\n",yytext);
					int k=hash_cal(yytext);
					struct stable temp;
					strcpy(temp.name,yytext);
					strcpy(temp.type,"identifier");
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
							if(strcmp(yytext,symbol_table[k].name)==0)
							{
								flag=1;
								break;
							}
							k=(k+1)%1000;
						}
					}
					if(flag==0)
					{
						symbol_table[k]=temp;
					}	
                	return (IDENTIFIER);
				}

{CONSTANT} {printf("%s - constant\n",yytext);
				int k=hash_cal(yytext);
					struct ctable temp;
					strcpy(temp.name,yytext);
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
							if(strcmp(yytext,constant_table[k].name)==0)
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

                    return (CONSTANT);
			}

\"[^\n]*\" {printf("%s - string\n",yytext);

				int k=hash_cal(yytext);
					struct ctable temp;
					strcpy(temp.name,yytext);
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
							if(strcmp(yytext,constant_table[k].name)==0)
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

				return(STRING_LITERAL);
			}

"+="			{ count(); return(ADD_ASSIGN); }
"-="			{ count(); return(SUB_ASSIGN); }
"*="			{ count(); return(MUL_ASSIGN); }
"/="			{ count(); return(DIV_ASSIGN); }
"%="			{ count(); return(MOD_ASSIGN); }
"++"			{ count(); return(INC_OP); }
"--"			{ count(); return(DEC_OP); }
"<="			{ count(); return(LE_OP); }
">="			{ count(); return(GE_OP); }
"=="			{ count(); return(EQ_OP); }
"!="			{ count(); return(NE_OP); }
";"			{ count(); return(';'); }
("{"|"<%")		{ count(); return('{'); }
("}"|"%>")		{ count(); return('}'); }
","			{ count(); return(','); }
":"			{ count(); return(':'); }
"="			{ count(); return('='); }
"("			{ count(); return('('); }
")"			{ count(); return(')'); }
("["|"<:")		{ count(); return('['); }
("]"|":>")		{ count(); return(']'); }
"."			{ count(); return('.'); }
"-"			{ count(); return('-'); }
"+"			{ count(); return('+'); }
"*"			{ count(); return('*'); }
"/"			{ count(); return('/'); }
"%"			{ count(); return('%'); }
"<"			{ count(); return('<'); }
">"			{ count(); return('>'); }
"?"			{ count(); return('?'); }

. {printf("ERROR - %s : invalid character at line [%d]\n",yytext,lineno);}

%%

int yywrap()
{
	return 1;
}
