%{
#include<string.h>
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

keyword "auto"|"double"|"int"|"struct"|"break"|"else"|"long"|"switch"|"case"|"enum"|"register"|"typedef"|"char"|"extern"|
		"return"|"union"|"const"|"float"|"short"|"unsigned"|"continue"|"for"|"signed"|"void"|"default"|"goto"|"sizeof"|
		"volatile"|"do"|"if"|"static"|"while"
identifier [A-Za-z_]([A-Za-z_]|[0-9])*
notid [0-9]+([A-Za-z_]|[0-9])*
number (([0-9])*)(\.(([0-9])+))?(([eE])([\+\-]?)(([0-9])+))?
ws " "|"	"|"\n"

spclsymb ";"|","|"#"|"("|")"|"["|"]"|"{"|"}"
op "&"|"+"|"-"|"*"|"/"|"%"|"="|"=="|"!="|"<"|">"|"<="|">="|"!"|"<>"|"?"|":"|"++"|"--"|"+="|"-="|"*="|"/="|"." 

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
			}

\/\/[^\n]*\n {lineno++;}

{keyword} {printf("%s - keyword\n",yytext);}
{number} {printf("%s - constant\n",yytext);
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
			}
{notid} {printf("ERROR - %s : ill-formed identifier at line [%d]\n",yytext,lineno);}
{identifier} {printf("%s - identifier\n",yytext);
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

				}
{spclsymb} {printf("%s - special character\n",yytext);}
{op} {printf("%s - operator\n",yytext);}
{ws} { if(yytext[0]=='\n') {lineno++;} }
. {printf("ERROR - %s : invalid character at line [%d]\n",yytext,lineno);}

%%

int main()
{
	int i;
	for(i=0;i<1000;i++)
	{
		symbol_table[i].name[0]='\0';
		symbol_table[i].type[0]='\0';
	}

	for(i=0;i<1000;i++)
	{
		constant_table[i].name[0]='\0';
		constant_table[i].type[0]='\0';
	}

	yyin = fopen("test2.txt","r");
	printf("******Tokens*****\n\n");
	yylex();
	if(comment_nesting!=0)
	{
		printf("ERROR : unterminated comment\n");
	}


	printf("\n*****Symbol Table******\n\n");
	for(i=0;i<1000;i++)
	{
		if(symbol_table[i].name[0]!='\0')
		{
			printf("%s	%s\n",symbol_table[i].name,symbol_table[i].type);
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
	return 0;
}
int yywrap()
{
	return 1;
}
