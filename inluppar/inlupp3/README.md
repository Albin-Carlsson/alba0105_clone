# Symbolic calculator
## Authors: 
### Emilio Funes, Annika Kuusrainen Alexandra Barbu

## How to build and run the program
In order to run the program the user must have installed Java Runtime Environment. To compile the program use the command 
\$make all  and run it by \$make run. In order to clean the class files, type \$make clean.

## Contents
This file includes the implementation of a basic symbolic calculator, which can parse and evaluate mathematical 
expressions symbolically. It supports operations like addition, subtraction, multiplication, division, and handling of 
variables, along with basic error handling for invalid expressions or operations.


## How to use the project
After running the command \$make run, you will be welcomed by "Welcome to Symbolic Calculator!" which means you were succesfully
able to start the program. Under it you should see the message "Enter expression: " and this is where the magic starts.
Supposedly, you inserted an expression, now this will be converted to an Abstract Syntax Tree, which will be evaluated to a result. 
You have acces to a library of already declared constants such as: $\pi$, *e*, L, and our special created variable *Answer* (42 ;) ).
and some basic mathematical operations such as *Exp*, *Log*, *Sin*, *Cos* and *Neg* are also present.


## Good to know
Keep in mind that the program is case sensitive, for example write "Quit" not "quit" if you want to quit the program. 
The command inputs always start with an upper case letter, same thing for mathematical operations, such as Exp, Cos, Sin, 
Log, and Neg.

When assigning values to variables, write the desired variable on the right side of the equal sign, for example:
"3= x" will work, but "x=3" will not, since variable assignment isn't symmetrical.

### Design choices
The developers have chosen to implement checked exceptions as a way of managing errors, since checked exceptions enforce 
compile-time checks, ensuring a much smoother developmental process. 


