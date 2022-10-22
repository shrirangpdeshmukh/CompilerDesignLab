%{ 
   /* Definition section */
  #include <stdio.h>
  #include <stdlib.h>
  #include "Node.h"
  #include "lex.yy.c"
  void yyerror();
  void displayAST(node *x);
  int flag=0;
%}

%union {
  node *Node;
  int Value;
}

%type<Node> G E T F
%type<Value> NUMBER

%token NUMBER 

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
        displayAST($$);
        return 0; 
      };

E: E'+'T { node *PlusNode = createNode(1, 0, $1, $3); $$ = PlusNode; }
|  E'-'T { node *MinusNode  = createNode(1, 1, $1, $3); $$ = MinusNode; }
|  T     { $$ = $1; };

T: T'*'F { node *MulNode = createNode(1, 2, $1, $3); $$ = MulNode; }
|  T'/'F {
            if ($3->value == 0) {
                printf("Division by zero is invalid!");
                flag = 1;
                return -1;
            }
            node *DivNode = createNode(1, 3, $1, $3);
            $$ = DivNode;  
         }
|  T'%'F {
            if (!($3->value > 0) ) {
               printf("Modulus number should be positive!");
               flag = 1;
               return -1;
            }
            node *ModNode = createNode(1, 4, $1, $3);
	        $$ = ModNode;
         }
|   F    { $$ = $1; }; 

F: NUMBER { node *NumNode = createNode(0, $1, NULL, NULL); $$ = NumNode; }
| '('E')' { $$ = $2; }
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

void displayAST(node *x)
{
    printf("Preorder - Result: ");
    preorder(x);
    printf("\n");
    printf("Inorder -- Result: ");
    inorder(x);
    printf("\n");
}

void yyerror()
{
    printf("Entered arithmetic expression is invalid\n");
    flag = 1;
}