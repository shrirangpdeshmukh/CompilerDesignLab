%{ 
/* Definition section */
	#include "calc.tab.h"
%}


digit 		[0-9]
number      ({digit}+)(\.{digit}+)?
operators 	(\+|\*|\-|\/)
/* Rule Section */
%% 
{number} 	{ 
				yylval.val=atof(yytext); 
				return NUMBER; 
		 	} 
{operators} { return yytext[0]; } 
[\t\n ]     { return 0; }
 
%% 
int yywrap() 
{ 
	return 1; 
}
