# turing
## Abstract machine simulator 
![demo picture](https://github.com/drvladbancila/turing/blob/master/turingdemo.png)
This software lets you simulate a small computer with 100 cells of memory and three registers:  
* Instruction Register (IR): holds the instruction currently being decoded and executed.  
* Instruction Counter (IC): keeps track of the address of the memory cell that the IR is decoding.  
* Accumulator (ACC): it stores intermediate arithmetic results (that can be later saved on memory).  

You will be asked to enter the program one instruction at a time. The format of each word (instruction) must be:  
  `XXXX`  
where the first two digits are the "operation code" and the last two digits are the operand (the memory cell that the instruction will work with).  

### How to install
`git clone https://github.com/drvladbancila/turing`  
`cd turing`  
`chmod +x ./install.sh`  
`./install.sh`  
`turing` 

### These are the OPERATION CODES:
```
10 READ       -> reads a number from the keyboard and saves it  
11 WRITE      -> prints the content of a cell on screen  
20 LOAD       -> loads the content of a cell into the accumulator  
21 STORE      -> stores the value of the accumulator in a memory cell  
30 ADD        -> adds the value of a cell to the accumulator  
31 SUB        -> subtracts  
32 MUL        -> multiplies  
33 DIV        -> divides  
40 BRANCH     -> jumps to the memory cell passed as operand  
41 BRANCHNEG  -> jumps to the memory cell passed as operand if the accumulator is zero  
42 BRANCHZERO -> jumps to the memory cell passed as operand if the accumulator is negative  
43 HALT       -> ends the execution of the program  
99999         -> sentinel value, makes turing stop taking inputs  
-99999        -> quit turing  
```

### Run program from file  
If you write a program on a file, you can run it in this way:  
`turing -f <file_name> [-d]`  
substituting `<file_name>` with your actual file. Remember that the file must contain valid instructions (see the next paragraph for the syntax of turing language) otherwise you will be prompted with syntax errors.  
The -d flag tells the program to dump the memory on screen after the execution is over (optional).  

### The syntax of the TURING LANGUAGE is the following:  
```
VAR XX N    -> stores N in the memory at address XX  
PRINT XX    -> prints the value contained at address XX  
LOAD XX     -> loads the content of XX into the accumulator  
STORE XX    -> stores the content of the accumulator into the memory cell at address XX  
ADD XX      -> adds the value contained at cell XX to the accumulator  
SUB XX      -> subtracts  
MUL XX      -> multiplies  
DIV XX      -> divides  
JUMP XX     -> works like BRANCH (see above)  
JUMPNEG XX  -> works like BRANCHNEG (see above)  
JUMPZERO XX -> works like BRANCHZERO (see above)  
HALT        -> ends the execution  
```
You can find some program examples in the 'examples' folder.  
That's it.  
