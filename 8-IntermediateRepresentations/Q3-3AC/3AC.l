%{ 
/* Definition section */
  #include "3AC.tab.h"
%}


digits 		  [0-9]+
id          [a-z]
operators 	(\+|\*|\-|\/|\%)
parantheses [()]
/* Rule Section */
%% 
{digits} 		    { 
                  yylval.Value = yytext[0];
                  return NUMBER; 
		 		        } 
{id}            {
                  yylval.Value = yytext[0];
                  return ID;
                }
{operators} 	  { return yytext[0]; } 
{parantheses} 	{ return yytext[0];}
[\t\n ]     	  { return 0; }
.				        { printf("Invalid operator %s", yytext); exit(0); }
%% 

int yywrap() 
{ 
	return 1; 
}