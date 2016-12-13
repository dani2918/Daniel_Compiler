* C- compiler version C-F16
* Built: 
* Author: Matthew Daniel
* File compiled: /Users/MattDaniel/Desktop/CS_445/Daniel_Compiler/testDataA7/array2.c-
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION input
  1:     ST  3,-1(1)	Store return address 
  2:     IN  2,2,2	Grab int input 
  3:     LD  3,-1(1)	Load return address 
  4:     LD  1,0(1)	Adjust fp 
  5:    LDA  7,0(3)	Return 
* END FUNCTION input
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION output
  6:     ST  3,-1(1)	Store return address 
  7:     LD  3,-2(1)	Load parameter 
  8:    OUT  3,3,3	Output integer 
  9:    LDC  2,0(6)	Set return to 0 
 10:     LD  3,-1(1)	Load return address 
 11:     LD  1,0(1)	Adjust fp 
 12:    LDA  7,0(3)	Return 
* END FUNCTION output
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputb
 13:     ST  3,-1(1)	Store return address 
 14:    INB  2,2,2	Grab bool input 
 15:     LD  3,-1(1)	Load return address 
 16:     LD  1,0(1)	Adjust fp 
 17:    LDA  7,0(3)	Return 
* END FUNCTION inputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputb
 18:     ST  3,-1(1)	Store return address 
 19:     LD  3,-2(1)	Load parameter 
 20:   OUTB  3,3,3	Output bool 
 21:    LDC  2,0(6)	Set return to 0 
 22:     LD  3,-1(1)	Load return address 
 23:     LD  1,0(1)	Adjust fp 
 24:    LDA  7,0(3)	Return 
* END FUNCTION outputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputc
 25:     ST  3,-1(1)	Store return address 
 26:    INC  2,2,2	Grab char input 
 27:     LD  3,-1(1)	Load return address 
 28:     LD  1,0(1)	Adjust fp 
 29:    LDA  7,0(3)	Return 
* END FUNCTION inputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputc
 30:     ST  3,-1(1)	Store return address 
 31:     LD  3,-2(1)	Load parameter 
 32:   OUTC  3,3,3	Output char 
 33:    LDC  2,0(6)	Set return to 0 
 34:     LD  3,-1(1)	Load return address 
 35:     LD  1,0(1)	Adjust fp 
 36:    LDA  7,0(3)	Return 
* END FUNCTION outputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outnl
 37:     ST  3,-1(1)	Store return address 
 38:  OUTNL  3,3,3	Output a newline 
 39:     LD  3,-1(1)	Load return address 
 40:     LD  1,0(1)	Adjust fp 
 41:    LDA  7,0(3)	Return 
* END FUNCTION outnl
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION ford
 42:     ST  3,-1(1)	Store return address. 
* COMPOUND
* Compound Body
* EXPRESSION
 43:     LD  3,-2(1)	Load address of base of array x
 44:     ST  3,-4(1)	Save left side 
 45:    LDC  3,3(6)	Load integer constant 
 46:     LD  4,-4(1)	Load left into ac1 
 47:    SUB  3,4,3	compute location from index 
 48:     LD  3,0(3)	Load array element 
 49:     ST  3,-3(1)	Store variable y
* EXPRESSION
*                       Begin call to  output
 50:     ST  1,-4(1)	Store old fp in ghost frame 
*                       Load param 1
 51:     LD  3,-3(1)	Load variable y
 52:     ST  3,-6(1)	Store parameter 
*                       Jump to output
 53:    LDA  1,-4(1)	Load address of new frame 
 54:    LDA  3,1(7)	Return address in ac 
 55:    LDA  7,-50(7)	CALL output
 56:    LDA  3,0(2)	Save the result in ac 
*                       End call to output
* EXPRESSION
 57:    LDC  3,3(6)	Load integer constant 
 58:     ST  3,-4(1)	Save index 
 59:    LDC  3,777(6)	Load integer constant 
 60:     LD  4,-4(1)	Restore index 
 61:     LD  5,-2(1)	Load address of base of array x
 62:    SUB  5,5,4	Compute offset of value 
 63:     ST  3,0(5)	Store variable x
* END COMPOUND
* Add standard closing in case there is no return statement
 64:    LDC  2,0(6)	Set return value to 0 
 65:     LD  3,-1(1)	Load return address 
 66:     LD  1,0(1)	Adjust fp 
 67:    LDA  7,0(3)	Return 
* END FUNCTION ford
* FUNCTION main
 68:     ST  3,-1(1)	Store return address. 
* COMPOUND
* Compound Body
 69:    LDC  3,5(6)	load size of array y
 70:     ST  3,-2(1)	save size of array y
* EXPRESSION
 71:    LDC  3,3(6)	Load integer constant 
 72:     ST  3,-8(1)	Save index 
 73:    LDC  3,666(6)	Load integer constant 
 74:     LD  4,-8(1)	Restore index 
 75:    LDA  5,-3(1)	Load address of base of array y
 76:    SUB  5,5,4	Compute offset of value 
 77:     ST  3,0(5)	Store variable y
* EXPRESSION
*                       Begin call to  ford
 78:     ST  1,-8(1)	Store old fp in ghost frame 
*                       Load param 1
 79:    LDA  3,-3(1)	Load address of base of array y
 80:     ST  3,-10(1)	Store parameter 
*                       Jump to ford
 81:    LDA  1,-8(1)	Load address of new frame 
 82:    LDA  3,1(7)	Return address in ac 
 83:    LDA  7,-42(7)	CALL ford
 84:    LDA  3,0(2)	Save the result in ac 
*                       End call to ford
 85:     LD  4,-8(1)	Restore index 
 86:    LDA  5,-3(1)	Load address of base of array y
 87:    SUB  5,5,4	Compute offset of value 
 88:     ST  3,0(5)	Store variable y
* EXPRESSION
*                       Begin call to  output
 89:     ST  1,-8(1)	Store old fp in ghost frame 
*                       Load param 1
 90:    LDA  3,-3(1)	Load address of base of array y
 91:     ST  3,-10(1)	Save left side 
 92:    LDC  3,3(6)	Load integer constant 
 93:     LD  4,-10(1)	Load left into ac1 
 94:    SUB  3,4,3	compute location from index 
 95:     LD  3,0(3)	Load array element 
 96:     ST  3,-10(1)	Store parameter 
*                       Jump to output
 97:    LDA  1,-8(1)	Load address of new frame 
 98:    LDA  3,1(7)	Return address in ac 
 99:    LDA  7,-94(7)	CALL output
100:    LDA  3,0(2)	Save the result in ac 
*                       End call to output
* END COMPOUND
* Add standard closing in case there is no return statement
101:    LDC  2,0(6)	Set return value to 0 
102:     LD  3,-1(1)	Load return address 
103:     LD  1,0(1)	Adjust fp 
104:    LDA  7,0(3)	Return 
* END FUNCTION main
  0:    LDA  7,104(7)	Jump to init [backpatch] 
* INIT
105:     LD  0,0(0)	Set the global pointer 
106:    LDA  1,0(0)	set first frame at end of globals 
107:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
108:    LDA  3,1(7)	Return address in ac 
109:    LDA  7,-42(7)	Jump to main 
110:   HALT  0,0,0	DONE! 
* END INIT
