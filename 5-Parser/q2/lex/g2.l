%{
    #include<stdio.h>
    #include<string.h>
    
    #include <bits/stdc++.h>
    using namespace std;
    
    int lines = 0;
    string yyval;
      
    
%}

delim               [ \t]
letter              [A-Za-z]
digit               [0-9]
id                  ({letter})({letter}|{digit})*
ws                  {delim}+
ic                  {digit}+
fc                  ({digit}+)(\.{digit}+)?(E[+-]?({digit})+)?
operator            (\+|\*|\/|\-|\=)
separator           [;,(){}]
assignment          :=
relop               [<>]
str                 ["]({letter}+)["]



%%
{ws}                {yyval=""; printf("Whitespace\n"); return 1;}
{separator}         {yyval = yytext; printf("Separator\n"); return 1;}
{relop}             {yyval = yytext; printf("Relop\n"); return 1;}
{operator}          {yyval = yytext; printf("operators\n"); return 1;}
{assignment}        {yyval = yytext; printf("Assignment\n"); return 1;}
"and"|"else"|"end"|"if"|"int"|"do"|"float"|"not"|"or"|"print"|"prog"|"scan"|"then"|"while" 
					{yyval = yytext; printf("Keyword: %s\n", yytext); return 1;}
{ic}            	{yyval = "ic"; printf("IC: %s\n", yytext); return 1;}
{fc}            	{yyval = "fc"; printf("FC: %s\n", yytext); return 1;}
{id}            	{yyval = "id"; printf("ID: %s\n", yytext); return 1;}
{str}           	{yyval = "str"; printf("STR: %s\n", yytext); return 1;}
\n                  {yyval= "", lines++;}
.                   {printf("ERROR: unknown token in input file: %s\n", yytext); return -1;}
%%


int yywrap(){return(1);}

int get_string(char *filename, string &res, map<string,string> terminal_map) {
    int token;
	yyin = fopen(filename, "r");
	while ((token = yylex()) != 0)
	{
		if (token == -1)
		{
			res = "ERROR$";
			return -1;
		}
		if (yyval == "")
		{
			continue;
		}
		res += terminal_map[yyval];
		yyval = "";
	}
	res += '$';
	printf("Lines Scanned %d\n", lines);
	return 0;
}