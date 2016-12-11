* C- compiler version C-F16
* Built: 
* Author: Matthew Daniel
* File compiled: /Users/MattDaniel/Desktop/CS_445/Daniel_Compiler/testDataA7/c05.c-
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
* FUNCTION main
 42:     ST  3,-1(1)	Store return address. 
* COMPOUND
* Compound Body
* EXPRESSION
 43:    LDC  3,2(6)	Load integer constant 
 44:     ST  3,-2(1)	Save index 
 45:    LDC  3,73(6)	Load integer constant 
 46:     LD  4,-2(1)	Restore index 
 47:    LDA  5,-1(0)	Load address of base of array x
 48:    SUB  5,5,4	Compute offset of value 
 49:     ST  3,0(5)	Store variable x
* EXPRESSION
 50:    LDC  3,1(6)	Load integer constant 
 51:     ST  3,-2(1)	Save index 
 52:    LDC  3,211(6)	Load integer constant 
 53:     LD  4,-2(1)	Restore index 
 54:    LDA  5,-5(0)	Load address of base of array y
 55:    SUB  5,5,4	Compute offset of value 
 56:     ST  3,0(5)	Store variable y
* EXPRESSION
*                       Begin call to  output
 57:     ST  1,-2(1)	Store old fp in ghost frame 
*                       Load param 1
 58:     LD  4,-4(1)	Restore index 
 59:    LDA  5,-1(0)	Load address of base of array x
 60:    SUB  5,5,4	Compute offset of value 
 61:     ST  3,0(5)	Store variable x
 62:     ST  3,-4(1)	Store parameter 
*                       Jump to output
 63:    LDA  1,-2(1)	Load address of new frame 
 64:    LDA  3,1(7)	Return address in ac 
 65:    LDA  7,-60(7)	CALL output
 66:    LDA  3,0(2)	Save the result in ac 
*                       End call to output
* EXPRESSION
*                       Begin call to  outnl
 67:     ST  1,-2(1)	Store old fp in ghost frame 
*                       Jump to outnl
 68:    LDA  1,-2(1)	Load address of new frame 
 69:    LDA  3,1(7)	Return address in ac 
 70:    LDA  7,-34(7)	CALL outnl
 71:    LDA  3,0(2)	Save the result in ac 
*                       End call to outnl
* END COMPOUND
* Add standard closing in case there is no return statement
 72:    LDC  2,0(6)	Set return value to 0 
 73:     LD  3,-1(1)	Load return address 
 74:     LD  1,0(1)	Adjust fp 
 75:    LDA  7,0(3)	Return 
* END FUNCTION main
  0:    LDA  7,75(7)	Jump to init [backpatch] 
* INIT
 76:     LD  0,0(0)	Set the global pointer 
 77:    LDA  1,-9(0)	set first frame at end of globals 
 78:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
 79:    LDA  3,1(7)	Return address in ac 
 80:    LDA  7,-39(7)	Jump to main 
 81:   HALT  0,0,0	DONE! 
* END INIT
