// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

@i
M=1

@R1
D=M
@n
M=D

@R2
M=0


(LOOP)
// condition
@i
D=M
@n
D=M-D
@STOP
D;JLT

// calc result
@R0
D=M
@R2
M=M+D
// increment
@i
M=M+1
@LOOP
0;JMP


(STOP)
// @R2
// M=D

(END)
@END
0;JMP