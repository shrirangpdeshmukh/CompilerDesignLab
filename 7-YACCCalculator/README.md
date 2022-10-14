# Compiler Design - Assignment 8
## Shrirang Prashant Deshmukh | 19CS01065

**Basic YACC Calculator**

### Part 1

**CFG**

```
G -> E
E -> E + T | E - T | T
T ->  T * F  |  T / F  | F
F -> num

// Where num is [0-9]+
```

- Proof this is fit for LR Parsing is done in the [PDF](./Q1.pdf)


**Attribute grammar**

```
AS(G) = AS(E) = AS(T) = AS(F) = { val }


G -> E          {G.val = E.val} 
E -> E + T      {E1.val = E2.val + T.val} 
E -> E - T      {E1.val = E2.val - E’.val} 
E -> T          {E.val = T.val}
T -> T * F      {T1.val = T2.val * F.val} 
T -> T / F      {T1.val = T2.val / F.val} 
T -> F          {T.val = F.val} 
F -> num        {F.val = num} 
```


### Part 2

- Lex File - *calc.l* 
- YACC File - *calc.y*

Main program reads one line arithmetic expression of whole numbers with +, -, * and / from user.

Gives the value of the expression if it is valid, otherwise returns error message.


### Instructions for usage
```
1. yacc calc.y -d  
2. lex calc.l  
3. gcc calc.tab.c  
4. a.exe  
```

