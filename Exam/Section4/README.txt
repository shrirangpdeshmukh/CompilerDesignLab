
For both the parts took care of the variables that are explicitly declared with their types i.e. for example 
1. int a := 10 + 5; 
2. bool := 6 + 9;

and not 

1. b:= t;
2. c:= true || false;

Added Attribute of type integer to the program to keep track of the memory used in the program. The type variable is the point where explicitly the number of bytes are specified i.e. 4 for int and 1 for bool;

VarTable and TypeTable to keep track of the variable and its types are corresponding indexes.

Since we've only two data types with unique sizes used them to determine the type while adding to the table maintaining the variable names with their respective types.