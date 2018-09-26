# turing
## Abstract machine simulator 

This software lets you simulate a small computer with  
100 cells of memory. You will be asked to enter the program  
one instruction at a time.  
The format of each word must be:  
  XXXX   
where the first two digits are the operation code and the last  
two digits are the operand (the memory cell which the instruction  
will work with).  

### How to install
`git clone https://github.com/drvladbancila/turing`  
`cd turing`  
`chmod +x ./install.sh`  
`./install.sh`  
`turing` 

### These are the OPERATION CODES:
```
10 READ -> read a number from the keyboard and saves it  
11 WRITE -> print the content of a cell on screen  
20 LOAD -> load the content of a cell on the accumulator  
21 STORE -> store the value of the accumulator on a memory cell  
30 ADD -> add the value of a cell to the accumulator  
31 SUB -> subtract 
32 MUL -> multiply  
33 DIV -> divide
40 BRANCH -> jump to the memory cell passed as operand  
41 BRANCHNEG -> jump to the memory cell passed as operand if the accumulator is zero  
42 BRANCHZERO -> jump to the memory cell passed as operand if the accumulator is negative  
43 HALT -> end the execution of the program  
-99999 -> sentinel value, will stop taking inputs  
```
### Run program from file  
If you write a program, you can run it in this way:  
`turing -f <file_name> [-d]`  
The -d flag tells the program to dump the memory after  
the execution is over (optional).  

### The syntax of the TURING LANGUAGE is the following:  
```
VAR XX N -> store N in the XX cell  
PRINT XX -> print the value of the XX cell  
LOAD, STORE, ADD, SUB, MUL, DIV as above  
JUMP instead of BRANCH  
JUMPNEG instead of BRANCHNEG  
JUMPZERO instead of BRANCHZERO  
HALT -> end the execution  
```
You can find some program examples in the 'examples' folder.  
That's it.  
