%{ 
/* Definition section */
	#include "calc.tab.h"
	extern int yylval; 
%}


digits 		[0-9]
operators 	(\+|\*|\-|\/)
/* Rule Section */
%% 
{digits} 	{ 
				yylval=atoi(yytext); 
				return NUMBER; 
		 	} 
{operators} { return yytext[0]; } 
[\t\n ]     { return 0; }
 
%% 
int yywrap() 
{ 
	return 1; 
}
