// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

    @KBD
    D=A
    @screenEnd
    M=D

(LOOP)
    @KBD
    D=M

    @CLEAR_SCR
    D;JEQ

    @i
    M=0

(FILL_REG)
    @SCREEN
    D=A
    @i
    D=D+M
    @screenEnd
    D=M-D
    @LOOP
    D;JEQ


    @SCREEN
    D=A
    @i
    A=D+M
    M=-1

    @i
    M=M+1

    @FILL_REG
    0;JMP

(CLEAR_SCR)
    @i
    M=0

(CLEAR_REG)
    @SCREEN
    D=A
    @i
    D=D+M
    @screenEnd
    D=M-D
    @LOOP
    D;JEQ


    @SCREEN
    D=A
    @i
    A=D+M
    M=0

    @i
    M=M+1

    @CLEAR_REG
    0;JMP
