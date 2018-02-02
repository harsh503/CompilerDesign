%token ID NUM 
%{
#include<stdio.h>
%}
%%
STATEMENT: E
E:E K E
|ID
|NUM
;
K:ID
;

%%
int yyerror()
{
    printf("parsing error %d",lineno);
    return (1);
}
main()
{
    yyparse();
}
