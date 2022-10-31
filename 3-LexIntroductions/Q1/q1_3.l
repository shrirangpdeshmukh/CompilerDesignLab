%{
#include<stdio.h>
#include<string.h>
%}

/*Binary strings with even integer equivalent means the unit place in binary representation in 0.*/

%%
(0|1)*0$          {printf("Accepted\n");}
.*                {printf("Rejected\n");}
%%

int yywrap() { return (1); }

int main()
{
    int token;
    yyin = fopen("test1_3.txt", "r");
    while ((token = yylex()) != 0)
    {
        printf("%d %s \n", token, yytext);
    }
}