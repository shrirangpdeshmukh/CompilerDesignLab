%{ 
   /* Definition section */
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  #include "lex.yy.c"
  
  void yyerror();
  char codeTable[100][4];
  void printResult();
  char addToTable(char op1, char operation, char op2);
  int currentIndex = 0;
  int flag=0;
%}

%union {
  char Value;
}

%type<Value> G E T F 
%token<Value>ID NUMBER



/* Precedence section */
%left '+' '-'
%left '*' '/' 
%left '%'
%left '(' ')'


%start G

/* Rule Section */
%%
G: E  { 
        $$ = $1;
        printResult();
        return 0; 
      };

E: E'+'T { 
            char AddCode = addToTable($1, '+', $3);
            $$ = AddCode; 
            
         }
|  E'-'T { 
            char MinusCode = addToTable($1, '-', $3);
            $$ = MinusCode;
            
         }
|  T     { $$ = $1; };

T: T'*'F {  
            char MulCode = addToTable($1, '*', $3);
            $$ = MulCode;
            
         }
|  T'/'F { 
            char DivCode = addToTable($1, '/', $3);
            $$ = DivCode; 
            
         }
|  T'%'F { 
            char ModCode = addToTable($1, '%', $3);
            $$ = ModCode; 
            
         }
|   F    { $$ = $1; }; 

F: ID       { $$ = $1; }
|  NUMBER   { $$ = $1; }
| '('E')'   { $$ = $2; }
%%


// driver code
void main()
{
    printf("Enter any arithmetic expression of whole numbers with +,-,*,/ and %% only\n");
    yyparse();
    if (flag == 0)
    {
        printf("Entered arithmetic expression is valid\n");
    }
}


void printResult()
{
    printf("\nResult\n");
    int i=0;
    for (i = 0; i < currentIndex; i++)
    {
        char *tableRow = codeTable[i];
        printf("%c := %c %c %c\n", tableRow[0], tableRow[1], tableRow[2], tableRow[3]);
    }
    printf("\n");
}

char addToTable(char op1, char operation, char op2) 
{
    char ID = 'A' + currentIndex;
    char *tableRow = codeTable[currentIndex];
    tableRow[0] = ID;
    tableRow[1] = op1;
    tableRow[2] = operation;
    tableRow[3] = op2;
    
    currentIndex++;
    return ID;
}

void yyerror()
{
    printf("Entered arithmetic expression is invalid\n");
    flag = 1;
}