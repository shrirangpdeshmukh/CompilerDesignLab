%{ 
    #include <stdio.h> 
    #include "lex.yy.c"
    int flag=0; 
    void yyerror(const char *str);
    void insertToTable(char *str, int typeSize);
    void displayVariableTypes();
    int currentIndex = 0;
    char varTable[50][10];
    int typeTable[50];
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

%union {
    int mem;
    char var[10];
}

%type<mem> S prog construct block stmtList stmt declStmt ifStmt whileStmt elsePart type
%type<var> ID assignmentStmt

%%

S: prog
{ 
	$$ = $1;
    printf("Successfully parsed\n\n"); 
    printf("Memory used: %d\n", $$);
    displayVariableTypes();
	return 0; 
}; 

prog : MAIN construct {$$ = $2;};

construct: LEFT_BRACE block RIGHT_BRACE {$$ = $2;};

block : stmtList {$$ = $1;}
| {};

stmtList: stmtList stmt {$$ = $1 + $2;} 
| stmt {$$ = $1;};

stmt: declStmt SEMICOLON {$$ = $1;}
|assignmentStmt SEMICOLON {$$ = 0;}
|readStmt SEMICOLON {$$ = 0;}
|printStmt SEMICOLON {$$ = 0;}
|ifStmt {$$ = $1;}
|whileStmt {$$ = $1;};

type: INT {$$ = 4;} 
| BOOL {$$ = 1;};

declStmt: type ID {$$ = $1; insertToTable($2, $1);} 
| type assignmentStmt {$$ = $1; insertToTable($2, $1);};

assignmentStmt: ID ASSIGN bExp {strcpy($$, $1);};

readStmt: INPUT {};

printStmt: OUTPUT {};

ifStmt: IF LEFT_PAREN bExp RIGHT_PAREN construct elsePart {$$ = $5 + $6;} 

elsePart:  ELSE construct {$$ = $2;} 
| {$$ = 0;};

whileStmt: WHILE LEFT_PAREN bExp RIGHT_PAREN construct {$$ = $5;};

bExp:  bExp AND bExp {}
| bExp OR bExp {} 
| NOT bExp {} 
| BOOL_CONST {} 
| aExp RELOP aExp {} 
| aExp {};

aExp: aExp OP aExp {} 
| ID {}
| INT_CONST {}

%%

 
void main()
{
    // Open the file
    extern FILE *yyin;
    yyin = fopen("q4.txt", "r");
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

void insertToTable(char *str, int typeSize)
{
    strcpy(varTable[currentIndex], str);
    typeTable[currentIndex] = typeSize == 1 ? 0 : 1;
    currentIndex++;
}

void displayVariableTypes()
{
    printf("\nVariables and types\n");
    for (int i = 0; i < currentIndex; i++)
    {
        printf("%s -> %s\n", varTable[i], typeTable[i] == 0 ? "bool" : "int");
    }
}