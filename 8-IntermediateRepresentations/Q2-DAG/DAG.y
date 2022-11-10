%{ 
   /* Definition section */
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  #include "Node.h"
  #include "lex.yy.c"
  
  void yyerror();
  void postorder(node *x, int visited[]);
  void printResult(node *root);
  int checkIfExpressionExists(char expression[100]);
  void addToDAG(node *newNode);
  node *processOperationNode(char expression[100], int isOp, char type, node *left, node *right);
  
  node* dag[100];
  int currentIndex = 0;
  int flag=0;
%}

%union {
  node *Node;
  char Value;
}

%type<Node> G E T F
%type<Value> ID

%token ID 

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
        printResult($$);
        return 0; 
      };

E: E'+'T { 
            char temp[100];
            sprintf(temp,"%s + %s", $1->expression, $3->expression);
        
            node *PlusNode = processOperationNode(temp, 1, '+', $1, $3);
            $$ = PlusNode; 
            
         }
|  E'-'T { 
            char temp[100];
            sprintf(temp,"%s - %s", $1->expression, $3->expression);
            
            node *MinusNode = processOperationNode(temp, 1, '-', $1, $3);
            $$ = MinusNode; 
            
         }
|  T     { $$ = $1; };

T: T'*'F {  
            char temp[100];
            sprintf(temp,"%s * %s", $1->expression, $3->expression);
            
            node *MulNode = processOperationNode(temp, 1, '*', $1, $3);
            $$ = MulNode; 
            
         }
|  T'/'F { 
            char temp[100];
            sprintf(temp,"%s / %s", $1->expression, $3->expression);
            
            node *DivNode = processOperationNode(temp, 1, '/', $1, $3);
            $$ = DivNode; 
            
         }
|  T'%'F { 
            char temp[100];
            sprintf(temp,"%s %% %s", $1->expression, $3->expression);
            
            node *ModNode = processOperationNode(temp, 1, '%', $1, $3);
            $$ = ModNode; 
            
         }
|   F    { $$ = $1; }; 

F: ID   { 
            char temp[100];
            sprintf(temp,"%c", $1);
            
            node *IDNode = processOperationNode(temp, 0, $1, NULL, NULL);
            $$ = IDNode; 
            
        }
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


void printResult(node *root)
{
    printf("\nResult\n");
    int visited[currentIndex];
    int i;
    for (i = 0; i < currentIndex; i++)
    {
        visited[i] = 0;
    }
    postorder(root, visited);
    printf("\n");
}

void postorder(node *x, int visited[])
{
  if(x==NULL)
    return;

  if(visited[x->id]){
    printf("node: %s (done)\n", x->expression);
    return;
  }

  visited[x->id] = 1;

  postorder(x->left,visited);
  postorder(x->right,visited);

  printf("node: %c\n",x->type);

}

int checkIfExpressionExists(char expression[100])
{
    int i;
    for (int i = 0; i < currentIndex; i++)
    {
        if (strcmp(dag[i]->expression, expression) == 0)
        {
            return i;
        }
    }
    return -1;
}

void addToDAG(node *newNode)
{
    dag[currentIndex] = newNode;
    currentIndex++;
}

node *processOperationNode(char expression[100], int isOp, char type, node *left, node *right)
{

    int index = checkIfExpressionExists(expression);

    if (index >= 0)
    {
        return dag[index];
    }
    else
    {
        node *newnode = createNode(currentIndex, isOp, type, expression, left, right);
        addToDAG(newnode);
        return newnode;
    }
}

void yyerror()
{
    printf("Entered arithmetic expression is invalid\n");
    flag = 1;
}