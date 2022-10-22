%{ 
/* Definition section */
  #include "DAG.tab.h"
%}


id		 	[a-z]
operators 	(\+|\*|\-|\/|\%)
parantheses [()]
/* Rule Section */
%% 
{id} 			{ 
					yylval.Value = yytext[0];
					return ID; 
		 		} 
{operators} 	{ return yytext[0]; } 
{parantheses} 	{ return yytext[0];}
[\t\n ]     	{ return 0; }
.				{ printf("Invalid operator %s", yytext); exit(0); }
%% 

int yywrap() 
{ 
	return 1; 
}