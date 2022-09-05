%{
    #include<stdio.h>
    #include<string.h>
    #include<bits/stdc++.h>

    
    //Token types
    
    #define LB 1
    #define RB 2
    #define PLUS 3
    #define MUL 4
    #define ID 5
    
    char yychar;
    
    
%}


letter      [A-Za-z]
digit       [0-9]
id          {letter}({letter}|{digit})*

%%
"+"         {yychar='+';    return(PLUS);}
"*"         {yychar='*';    return(MUL);}
")"         {yychar=')';    return(RB);}
"("         {yychar='(';    return(LB);}
{id}        {yychar='i';    return(ID);}
.           {printf("ERROR: unknown token %s\n", yytext); return -1;}
%%

int yywrap(){return(1);}

int get_string(char *filename, string &res) {
    int token;
    int i = 0;
    yyin = fopen(filename, "r");
    while ((token = yylex()) != 0)
    {
        if (token == -1) {
            res = "ERROR$";
            return -1;
        }
        
        res += yychar;
    }
    res+='$';
    
    return 0;

    
}