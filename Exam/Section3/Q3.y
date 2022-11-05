%{ 
    #include <stdio.h> 
    #include "lex.yy.c"
    int flag=0; 
    void yyerror(const char *str);
%} 

/* Definitions */
%locations

%token MAIN SEMICOLON INT BOOL ID ASSIGN INPUT OUTPUT IF ELSE WHILE RELOP OP INT_CONST BOOL_CONST LEFT_BRACE RIGHT_BRACE LEFT_PAREN RIGHT_PAREN AND OR NOT
%start S


%left OP
%nonassoc RELOP
%left OR
%left AND
%nonassoc NOT
%left LEFT_PAREN RIGHT_PAREN
%left LEFT_BRACE RIGHT_BRACE
%nonassoc IF 
%nonassoc ELSE
%nonassoc WHILE

%%

S: prog
{ 
	printf("Successfully parsed"); 
	return 0; 
}; 
prog : MAIN construct {};

construct: LEFT_BRACE block RIGHT_BRACE {};

block : stmtList | {};

stmtList: stmtList stmt {} | stmt {};

stmt: declStmt SEMICOLON {}
|assignmentStmt SEMICOLON {}
|readStmt SEMICOLON {}
|printStmt SEMICOLON {}
|ifStmt {}
|whileStmt {};

type: INT {} | BOOL {};
declStmt: type ID {} | type assignmentStmt {};
assignmentStmt: ID ASSIGN bExp {};
readStmt: INPUT {};
printStmt: OUTPUT {};
ifStmt: IF LEFT_PAREN bExp RIGHT_PAREN construct elsePart {} 
elsePart:  ELSE construct {} | {};
whileStmt: WHILE LEFT_PAREN bExp RIGHT_PAREN construct {};
bExp:  bExp AND bExp {}| bExp OR bExp {} | NOT bExp {} | aExp RELOP aExp {} | BOOL_CONST {} | aExp {};

aExp: aExp OP aExp {} 
| ID {}
| INT_CONST {}

%%

 
void main()
{
    // Open the file
    extern FILE *yyin;
    yyin = fopen("q3.txt", "r");
    if (yyin == NULL)
    {
        printf("Could not open file\n");
        return;
    }

    // Parse
    yyparse();

    // Successful parsing
    if (flag == 0)
    {
        printf("\nEntered program is valid\n");
    }
}

// Error handling
void yyerror(const char *str)
{

    printf("Error at Line: %d - %s\n%s\n", yylineno, yytext, str);
    flag = 1;
}