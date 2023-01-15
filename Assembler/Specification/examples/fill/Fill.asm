// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

// Can be refactored but I don't want to do it

(LOOP)
@SCREEN
D=A
@addr
M=D
@8192
D=A
@n
M=D

// reset i
@i 
M=1


@KBD
D=M
@DRAW_WHITE
D;JEQ
@DRAW_BLACK
0;JMP

(DRAW_WHITE)
// condition
@i 
D=M
@n
D=M-D
@LOOP
D;JLT

// set white color
@addr
A=M
M=0
@addr
M=M+1

@i
M=M+1

@DRAW_WHITE
0;JMP


(DRAW_BLACK)
// condition
@i 
D=M
@n
D=M-D
@LOOP
D;JLT

// set black color
@addr
A=M
M=-1
@addr
M=M+1

@i
M=M+1

@DRAW_BLACK
0;JMP

