%{
#include<stdio.h>
#include<string.h>
%}


skip    [efv]
delim   [ \t]
ws      {delim}+

%%
{skip}      { printf("#"); }
{ws}        { }
.           { printf("%s", yytext); }
%%

int yywrap() { return (1); }

int main()
{
    int token;
    yyin = fopen("q2_2.txt", "r");
    printf("\n");
    while ((token = yylex()) != 0) {}
}