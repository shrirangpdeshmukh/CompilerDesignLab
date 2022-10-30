%{ 
    #include <stdio.h> 
    #include <stdlib.h>
    #include <string.h>
    #include "lex.yy.c"
    int flag=0; 
    
    void yyerror(char *str);
    void new_variable();
    int new_line_label();
    
    int variable_count = 0;
    int line_label_count = 0;
    
    char variable[10];
    int else_ref = 0;
    int if_true_ref = 10;  
    int while_ref = 0;
    int while_false_ref = 0;
    FILE *outfile ; 
%} 

/* Definitions */

%token AND ASSIGN COLON DIV ELSE END EQ  GE GLOBAL GT IF LEFT_PAREN LE LT MINUS MOD MULT NE NOT OR PLUS PRINT READ RIGHT_PAREN SEMICOLON WHILE 

%left PLUS MINUS
%left MULT DIV MOD
%left AND OR
%nonassoc NOT
%left LEFT_PAREN RIGHT_PAREN
%nonassoc IF
%nonassoc ELSE

%start S

%union
{ 	
	char val[100];
}
   
%type<val> exp relOP bExp
%token<val> ID INT_CONST


/* Rule Section */
%% 
S:          prog {}; 

prog :      GLOBAL stmtListO END { fprintf(outfile, " exit\n"); };

stmtListO:  stmtList {} 
            | {};
            
stmtList:   stmtList SEMICOLON stmt {}  
            | stmt {};
            
stmt:       assignmentStmt {}
            | readStmt {}
            | printStmt {}
            | ifStmt {}
            | whileStmt {};

assignmentStmt: ID ASSIGN exp { fprintf(outfile, " %s = %s\n", $1, $3); };

readStmt:   READ ID { 
                new_variable();
                fprintf(outfile, " %s = Read %s\n", variable, $2); 
            } ;

printStmt:  PRINT ID { fprintf(outfile, " print %s\n", $2); };

ifStmt:     IF bExp {
  
              new_variable();
              else_ref = new_line_label();
              fprintf(outfile, " %s = %s\n", variable, $2);
              fprintf(outfile, " If ! (%s) goto L%d\n", variable, else_ref);
              
            } 
            COLON stmtList elsePart END;

elsePart:   ELSE { 
  
              if_true_ref = new_line_label();
              fprintf(outfile, " goto L%d\n", if_true_ref);
              fprintf(outfile, " L%d : ", else_ref);
              else_ref--;
               
            } stmtList { fprintf(outfile, " L%d : ", if_true_ref); }
            | { 
                fprintf(outfile, " L%d : ", else_ref); 
                else_ref--;
            };

whileStmt:  WHILE {
              
              while_ref = new_line_label();
              fprintf(outfile, " L%d : ", while_ref);
  
            } bExp {
              
              while_false_ref = new_line_label();
              fprintf(outfile, " If ! (%s) goto L%d\n", $3, while_false_ref); 
              
            } COLON stmtList {
              
              fprintf(outfile, " goto L%d\n", while_ref); 
              fprintf(outfile, " L%d : ", while_false_ref);
              while_false_ref-=2;
              while_ref-=2;
              
            }
            
            END;

bExp:       bExp OR bExp {
                new_variable();
                fprintf(outfile, " %s = %s or %s\n", variable, $1, $3);
                strcpy($$, variable);
            }
            | bExp AND bExp {
                new_variable();
                fprintf(outfile, " %s = %s and %s\n", variable, $1, $3);
                strcpy($$, variable);
            }
            | NOT bExp {
                new_variable();
                fprintf(outfile, " %s = !%s\n", variable, $2);
                strcpy($$, variable);
            }
            | LEFT_PAREN bExp RIGHT_PAREN {
                new_variable();
                fprintf(outfile, " %s = %s\n", variable, $2);
                strcpy($$, variable);
            }
            | exp relOP exp {
                new_variable();
                fprintf(outfile, " %s = %s %s %s\n", variable, $1, $2, $3);
                strcpy($$, variable);
            };

relOP:      EQ { strcpy($$, "=="); }
            | LE { strcpy($$, "<="); }
            | LT { strcpy($$, "<"); }
            | GE { strcpy($$, ">="); }
            | GT { strcpy($$, ">"); }
            | NE { strcpy($$, "!="); };

exp:        exp PLUS exp {
                new_variable();
                fprintf(outfile, " %s = %s + %s\n", variable, $1, $3);
                strcpy($$, variable);
            }
            | exp MINUS exp {
                new_variable();
                fprintf(outfile, " %s = %s - %s\n", variable, $1, $3);
                strcpy($$, variable);
            }
            | exp MULT exp {
                new_variable();
                fprintf(outfile, " %s = %s * %s\n", variable, $1, $3);
                strcpy($$, variable);
            }
            | exp DIV exp {
                new_variable();
                fprintf(outfile, " %s = %s / %s\n", variable, $1, $3);
                strcpy($$, variable);
            }
            | exp MOD exp {
                new_variable();
                fprintf(outfile, " %s = %s %% %s\n", variable, $1, $3);
                strcpy($$, variable);
            }
            | MINUS exp {
                new_variable();
                fprintf(outfile, " %s = -%s\n", variable, $2);
                strcpy($$, variable);
            }
            | PLUS exp {
                new_variable();
                fprintf(outfile, " %s = +%s\n", variable, $2);
                strcpy($$, variable);
            }
            | LEFT_PAREN exp RIGHT_PAREN {
                new_variable();
                fprintf(outfile, " %s = %s\n", variable, $2);
                strcpy($$, variable);
            }
            | ID {}
            | INT_CONST {};
%%


int main()
{
    extern FILE *yyin;
    yyin = fopen("input.txt", "r");

    if (yyin == NULL)
    {
        printf("Could not open input file\n");
        return -1;
    }

    outfile = fopen("out.txt", "w");
    fprintf(outfile, "Three Address Code:\n------------------------------------------\n");
    yyparse();
    if (flag == 0)
    {
        printf("Program parsed Successfully\n");
    }
}

void yyerror(char *str)
{
    printf("\nError at Line: %d -- %s\n", yylineno, str);
    flag = 1;
}

void new_variable()
{
    char res[10];
    sprintf(res, "T%d", variable_count++);
    strcpy(variable, res);
}

int new_line_label()
{
    int res = line_label_count++;
    return res;
}
