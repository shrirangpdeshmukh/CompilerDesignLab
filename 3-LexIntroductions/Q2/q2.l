%{
    #include<stdio.h>
    #include<string.h>
    
    int yylval = -1;
    
    //Token types
    #define IF 1
    #define THEN 2
    #define ELSE 3
    #define ID 4
    #define NUM 5
    #define RELOP 6
    
    //Relop operator types
    #define LT 61
    #define LE 62
    #define EQ 63
    #define NE 64
    #define GT 65
    #define GE 66
    
%}


delim       [ \t\n]
ws          {delim}+
letter      [A-Za-z]
digit       [0-9]
id          {letter}({letter}|{digit})*
number      ({digit}+)(\.{digit}+)?(E[+-]?({digit})+)?

%%
{ws}        {printf("Whitespace\n");}
if          {return(IF);}
then        {return(THEN);}
else        {return(ELSE);}
{id}        {return(ID);}
{number}    {return(NUM);}
"<"         {yylval = LT; return(RELOP);}
"<="        {yylval = LE; return(RELOP);}
"="         {yylval = EQ; return(RELOP);}
"<>"        {yylval = NE; return(RELOP);}
">"         {yylval = GT; return(RELOP);}
">="        {yylval = GE; return(RELOP);}
.           {printf("ERROR: unknown token");}
%%

int yywrap(){return(1);}

int main(){
    int token;
    yyin=fopen("test2.txt","r");
    while ((token=yylex())!=0) {
        printf("Token: %d,\tText: %s,\tValue: %d\n", token, yytext, yylval);
        yylval = -1;
    }

}