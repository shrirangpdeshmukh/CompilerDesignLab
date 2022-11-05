%{
#include<stdio.h>
#include<string.h>
%}


/*Binary strings with even ones*/
alphabets [a-z]

%%
b{alphabets}*e     { printf("%s\nAccepted\n\n", yytext); }
.*                 { printf("%s\nRejected\n\n", yytext); }
%%

int yywrap() { return (1); }

int main()
{
    int token;
    yyin = fopen("q2_1.txt", "r");
    while ((token = yylex()) != 0)
    {
        printf("%d %s \n", token, yytext);
    }
}