%token ID NUM op spclsymb
%{
#include<stdio.h>
%}
%%
STATEMENT: E spclsymb
E:E K E
|ID
|NUM
;
K:op
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
