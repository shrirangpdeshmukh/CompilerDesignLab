%{
#include<stdio.h>
#include<string.h>
%}


/*Binary strings with even ones*/

%%
0*(10*1)*0*     {printf("Accepted\n");}
.*              {printf("Rejected\n");}
%%

int yywrap() { return (1); }

int main()
{
    int token;
    yyin = fopen("test1_1.txt", "r");
    while ((token = yylex()) != 0)
    {
        printf("%d %s \n", token, yytext);
    }
}