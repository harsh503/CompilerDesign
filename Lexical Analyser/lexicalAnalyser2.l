%{

int comment_nesting = 0; 
int lineno=1;

%}

keyword "auto"|"double"|"int"|"struct"|"break"|"else"|"long"|"switch"|"case"|"enum"|"register"|"typedef"|"char"|"extern"|"return"|"union"|"const"|"float"|"short"|"unsigned"|"continue"|"flor"|"signed"|"void"|"default"|"goto"|"sizeof"|"volatile"|"do"|"if"|"static"|"while"
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

\"[^\n]*\" {printf("%s - string\n",yytext);}

\/\/[^\n]*\n {lineno++;}

{keyword} {printf("%s - keyword\n",yytext);}
{number} {printf("%s - constant\n",yytext);}
{notid} {printf("ERROR - %s : ill-formed identifier at line [%d]\n",yytext,lineno);}
{identifier} {printf("%s - identifier\n",yytext);}
{spclsymb} {printf("%s - special character\n",yytext);}
{op} {printf("%s - operator\n",yytext);}
{ws} { if(yytext[0]=='\n') {lineno++;} }
. {printf("ERROR - %s : invalid character at line [%d]\n",yytext,lineno);}

%%

int main()
{
	yyin = fopen("test2.txt","r");
	yylex();
	if(comment_nesting!=0)
	{
		printf("ERROR : unterminated comment\n");
	}
	return 0;
}
int yywrap()
{
	return 1;
}
