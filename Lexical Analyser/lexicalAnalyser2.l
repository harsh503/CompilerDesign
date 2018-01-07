%{

int comment_nesting = 0;  /* Line 4 */

%}

keyword "auto"|"double"|"int"|"struct"|"break"|"else"|"long"|"switch"|"case"|"enum"|"register"|"typedef"|"char"|"extern"|"return"|"union"|"const"|"float"|"short"|"unsigned"|"continue"|"flor"|"signed"|"void"|"default"|"goto"|"sizeof"|"volatile"|"do"|"if"|"static"|"while"
identifier [A-Za-z_]([A-Za-z_]|[0-9])*
number [+|-]?(([0-9])+)(.(([0-9])+))?([e|E][+|-]?(([0-9])+))?
ws [ |	|\n]

spclsymb [\{\}\[\]\(\)]
arithop [\+\-\*\/\%] 

%x SC_COMMENT
 	
%%

"/*"             { BEGIN(SC_COMMENT); }
<SC_COMMENT>{
  "/*"           { ++comment_nesting; }
  "*"+"/"        { if (comment_nesting) --comment_nesting;
                   else BEGIN(INITIAL); }
  "*"+           ; /* Line 11 */
  [^/*\n]+       ; /* Line 12 */
  [/]            ; /* Line 13 */
  \n             ; /* Line 14 */
}

{keyword} {printf("keyword,%s\n",yytext);}
{number} {printf("number,%s\n",yytext);}
{identifier} {printf("identifier,%s\n",yytext);}
{spclsymb} {printf("spcl symbol,%s\n",yytext);}
{arithop} {printf("arithop,%s\n",yytext);}

{ws} ;



%%

int main()
{
	yyin = fopen("test2.txt","r");
	yylex();
	return 0;
}
int yywrap()
{
	return 1;
}
