%{
    #include"Q3.tab.h"
%}

%option yylineno

delim               [ \t\n]
letter              [A-Za-z]
digit               [0-9]
id                  ({letter})({letter}|{digit})*
ws                  {delim}+
int_const           {digit}+
operator            (\+|\*|\/|\-)
input_construct     in\({id}\) 
output_construct    out\({id}\) 
relop               (">"|">="|"<"|"<="|"=="|"!=")  
main                main\(\)
bool_const          ("true"|"false")


%%
{ws}                {}
{main}              { return MAIN; }
if                  { return IF; }
else                { return ELSE; }
while               { return WHILE; }
"&&"                  { return AND; }
"||"                  { return OR; }
"!"                   { return NOT; }
"int"|"INT"         { return INT; }
"bool"|"BOOL"       { return BOOL; }
{bool_const}        { return BOOL_CONST; }
:=                  { return ASSIGN; }
;                   { return SEMICOLON; }
[(]                 { return LEFT_PAREN; }
[)]                 { return RIGHT_PAREN; }
[{]                 { return LEFT_BRACE; }
[}]                 { return RIGHT_BRACE; }
{operator}          { return OP; }
{relop}             { return RELOP; }
{input_construct}   { return INPUT; }
{output_construct}  { return OUTPUT; }
{int_const}         { return INT_CONST; }
{id}                { return ID; }
.                   { printf("Error"); }
%%

int yywrap() { return (1); }