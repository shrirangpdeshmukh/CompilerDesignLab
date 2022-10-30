# Compiler Design - Assignment 10
## Shrirang Prashant Deshmukh | 19CS01065

**Extended 3 Address Code**

### Instructions for usage
```
1. yacc 3AC.y -d  
2. lex 3AC.l  
3. gcc 3AC.tab.c  
4. a.exe  
```
### Grammar 

```
S:          prog; 
prog :      GLOBAL stmtListO END;
stmtListO:  stmtList | #;
stmtList:   stmtList SEMICOLON stmt | stmt ;
stmt:       assignmentStmt | readStmt | printStmt | ifStmt | whileStmt;
assignmentStmt: ID ASSIGN exp;
readStmt:   READ ID;
printStmt:  PRINT ID;
ifStmt:     IF bExp COLON stmtList elsePart END;
elsePart:   ELSE stmtList | #;
whileStmt:  WHILE bExp COLON stmtList END;
bExp:       bExp OR bExp | bExp AND bExp | NOT bExp | LEFT_PAREN bExp RIGHT_PAREN  | exp relOP exp ;
relOP:      EQ | LE | LT | GE | GT | NE ;
exp:        exp PLUS exp  | exp MINUS exp | exp MULT exp | exp DIV exp | exp MOD exp | MINUS exp | PLUS exp | LEFT_PAREN exp RIGHT_PAREN | ID | INT_CONST;
```


