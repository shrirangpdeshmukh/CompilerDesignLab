%{ 
   /* Definition section */
  #include <stdio.h>
  #include "lex.yy.c"
  int flag=0;
  void yyerror();
%} 

%token NUMBER 

/* Precedence section */
%left '+' '-'
%left '*' '/'
%left '%'
%left '(' ')'

%start G

/* Rule Section */
%%
G: E  { $$ = $1;
        printf("\nResult=%d\n", $$); 
        return 0; 
      };

E: E'+'T {$$ = $1 + $3;}
|  E'-'T {$$ = $1 - $3;}
|  T     {$$ = $1;};

T:  T'*'F {$$ = $1 * $3;}
|   T'/'F {
            if ($3 == 0) {
                printf("Division by zero is invalid!");
                flag = 1;
                return -1;
            }
            $$ = $1 / $3;
            
          }
| T'%'F   {
            if (!($3 > 0) ) {
               printf("Modulus number should be positive!");
               flag = 1;
               return -1;
            }
            $$ = $1 % $3;
          }
|   F     {$$ = $1;}; 

F: NUMBER {$$ = $1;} 
| '('E')' {$$ = $2;};
%%


//driver code 
void main() 
{ 
   printf("Enter any arithmetic expression of whole numbers with +,-,* and / only\n");  
   yyparse();
   if(flag==0) {
        printf("Entered arithmetic expression is valid\n"); 
   }
} 
  
void yyerror() 
{ 
   printf("Entered arithmetic expression is invalid\n"); 
   flag=1; 
} 