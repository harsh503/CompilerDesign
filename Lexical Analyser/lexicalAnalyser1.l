%{

%}

letter [A-Za-z]
underscore _
digit [0-9]
digits (digit)+
keyword [(auto)|(double)|(int)|(struct)|(break)|(else)|(long)|(switch)|(case)|(enum)|(register)|(typedef)|(char)|(extern)|(return)|(union)|(const)|(float)|(short)|(unsigned)|(continue)|(for)|(signed)|(void)|(default)|(goto)|(sizeof)|(volatile)|(do)|(if)|(static)|(while)]
identifier [(letter)|(underscore)]([(letter)|(underscore)|(digit)])*
number [+|-]?(digits)(.(digits))?([e|E][+|-]?(digits))?
ws [ |	|\n]

%%

{keyword} {printf("keyword,%s\n",yytext);}
{number} {printf("number,%s\n",yytext);}
{identifier} {printf("identifier,%s\n",yytext);}

%x BLOCKCOMMENT
"/*"                 { yy_push_state(BLOCKCOMMENT); }
<BLOCKCOMMENT>"*/"   { if(yy_top_state() == BLOCKCOMMENT)
                           yy_pop_state();
                       else
                           fprintf(stderr,
                            "Error: comment close `*/` found while not in comment\n");
                     }
<BLOCKCOMMENT>.      { /* consume */ }

.                    { return yytext[0]; }

%%

int main()
{
	yyin = fopen("test1.txt","r");
	yylex();
	return 0;
}
int yywrap()
{
	return 1;
}
