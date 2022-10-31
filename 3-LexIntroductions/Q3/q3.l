%{
    #include<stdio.h>
    #include<string.h>
    
    int yylval = -1;
    int lines = 0;
    
    // Token_Types
    #define IF 1
    #define ELSE 2
    #define THEN 3
    #define RELOP 4
    #define ARITHMETIC 5
    #define ASSIGNMENT 6
    #define ID 7
    #define INTEGER 8
    #define FLOAT 9
    #define INT_NUM 10
    #define FLOAT_NUM 11
    #define FUNC 12
    #define LOOP 13
    #define SEPERATOR 14
    #define WHITESPACE 15
    #define IO_CONSTRUCT 16
    #define MAIN 17
    
    // Relop_operators types
    #define LT 41
    #define LE 42
    #define EQ 43
    #define NE 44
    #define GT 45
    #define GE 46
    
    //Arithmetic_operators types
    #define INCREMENT 51
    #define DECREMENT 52
    
    // I_O operator types
    #define INPUT_CONSTRUCT 161
    #define OUTPUT_CONSTRUCT 162
%}

delim               [ \t]
letter              [A-Za-z]
digit               [0-9]
id                  ({letter})({letter}|{digit})*
ws                  {delim}+
int_num             {digit}+
float_num           ({digit}+)(\.{digit}+)?(E[+-]?({digit})+)?
operator            (\+|\*|\/|\-)
seperator           [;,(){}]
assignment          ({operator})?=
input_construct     read\({id}\) 
output_construct    print\({id}\) 


%%
{ws}                {printf("Whitespace\n");}
{seperator}         {yylval = (int)yytext[0]; return (SEPERATOR);}
main\(\)            {return (MAIN);}
if                  {return(IF);}
then                {return(THEN);}
else                {return(ELSE);}
for                 {yylval = (int)yytext[0]; return(LOOP);}
while               {yylval = (int)yytext[0]; return(LOOP);}
{input_construct}   {yylval = INPUT_CONSTRUCT; return (IO_CONSTRUCT);}
{output_construct}  {yylval = OUTPUT_CONSTRUCT; return (IO_CONSTRUCT);}
"int"|"INT"         {return (INTEGER);}
"float"|"FLOAT"     {return (FLOAT);}
"++"                {yylval = INCREMENT; return (ARITHMETIC);}
"--"                {yylval = DECREMENT; return (ARITHMETIC);}
{int_num}           {return (INT_NUM);}
{float_num}         {return (FLOAT_NUM);}
{id}                {return(ID);}
{assignment}        { 
                        int answer = (int)yytext[0];
                        if (strlen(yytext) > 1) {
                            answer += (int)yytext[1];
                        }
                        yylval = answer; 
                        return (ASSIGNMENT);
                    }
{operator}          {yylval = (int)yytext[0]; return(ARITHMETIC);}
"<"                 {yylval = LT; return(RELOP);}
"<="                {yylval = LE; return(RELOP);}
"=="                {yylval = EQ; return(RELOP);}
"!="                {yylval = NE; return(RELOP);}
">"                 {yylval = GT; return(RELOP);}
">="                {yylval = GE; return(RELOP);}
\n                  {lines++;}
.                   {printf("Error");}
%%

int yywrap() { return (1); }

int main()
{
    int token;
    yyin = fopen("q3.txt", "r");
    while ((token = yylex()) != 0)
    {

        printf("Token: %d,\tText: %s,\tValue: %d\n", token, yytext, yylval);
        yylval = -1;
    }
    printf("Lines Read %d\n", lines);
}