%{
#include "y.tab.h"
#include<string.h>
#include<stdio.h>

int comment_nesting = 0; 
int lineno=1;

struct stable{
	char name[100];
	char type[50];
	long long int scope;
}symbol_table[100000];

struct ctable{
	char name[100];
	char type[50]; 
}constant_table[100000];
char yyval[100];
char yycons[100];
char yystr[100];

char currtype[100],prevtype[100],currid[100],previd[100];

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
CONSTANT (([0-9])*)(\.(([0-9])+))?(([eE])([\+\-]?)(([0-9])+))?
WHITESPACE " "|"	"|"\n"

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
  \n             { lineno++;}
}

\/\/[^\n]*[\n]? { lineno++; }

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
"float"			{ strcpy(prevtype, currtype); strcpy(currtype, yytext); return(FLOAT); }
"for"			{ return(FOR); }
"goto"			{ return(GOTO); }
"if"			{ return(IF); }
"int"			{ strcpy(prevtype, currtype); strcpy(currtype, yytext); return(INT); }
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
"void"			{ strcpy(prevtype, currtype); strcpy(currtype, yytext); return(VOID); }
"volatile"		{ return(VOLATILE); }
"while"			{ return(WHILE); }

{IDENTIFIER} 	{	//printf("%s - identifier\n",yytext);
					strcpy(yyval,yytext);
					strcpy(previd,currid);
					strcpy(currid,yytext);
                	return (IDENTIFIER);
				}

{CONSTANT} {//printf("%s - constant\n",yytext);
					strcpy(yycons,yytext);
					return (CONSTANT);
			}

\"[^\n]*\" {//printf("%s - string\n",yytext);

				strcpy(yystr,yytext);

				return(STRING_LITERAL);
			}

"+="|"-="|"*="|"/="|"%="	{ return(ASSIGN_OP); }
"=="|"!="						{ return(EQU_OP); }
"<="|">="|">"|"<"				{ return(REL_OP); }
"+"|"-"							{ return(ADD_OP); }
"*"|"/"|"%"						{ return(MUL_OP); }
"++"|"--"						{ return(INCDEC_OP); }
"&&"        {return(LAND);}
"||"        {return(LOR);}
"&"        {return(BAND);}
"|"        {return(BOR);}
"^"        {return(BXOR);}
"!"|"~"    {return(NOT_OP);}
"=" 		{ return('='); }
"{"			{ return('{'); }
"}"			{ return('}'); }
"("			{ return('('); }
")"			{ return(')'); }
"["			{ return('['); }
"]"			{ return(']'); }
";"			{ return(';'); }
","			{ return(','); }
"."			{ return('.'); }
"?"			{ return('?'); }
":"			{ return(':'); }

{WHITESPACE}	{ if(yytext[0]=='\n') { lineno++; } };

. {printf("LEXICAL ERROR - %s : invalid character at line [%d]\n",yytext,lineno);}

%%



int yywrap()
{
	return 1;
}