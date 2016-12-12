* C- compiler version C-F16
* Built: 
* Author: Matthew Daniel
* File compiled: /Users/MattDaniel/Desktop/CS_445/Daniel_Compiler/testDataA7/g06.c-
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
* FUNCTION cat
 42:     ST  3,-1(1)	Store return address. 
* COMPOUND
* Compound Body
* RETURN
 43:     LD  3,-2(1)	Load address of base of array z
 44:     ST  3,-3(1)	Save left side 
 45:    LDC  3,3(6)	Load integer constant 
 46:     LD  4,-3(1)	Load left into ac1 
 47:    SUB  3,4,3	compute location from index 
 48:     LD  3,0(3)	Load array element 
 49:    LDA  2,0(3)	Copy result to rt register 
 50:     LD  3,-1(1)	Load return address 
 51:     LD  1,0(1)	Adjust fp 
 52:    LDA  7,0(3)	Return 
* END COMPOUND
* Add standard closing in case there is no return statement
 53:    LDC  2,0(6)	Set return value to 0 
 54:     LD  3,-1(1)	Load return address 
 55:     LD  1,0(1)	Adjust fp 
 56:    LDA  7,0(3)	Return 
* END FUNCTION cat
* FUNCTION main
 57:     ST  3,-1(1)	Store return address. 
* COMPOUND
* Compound Body
 58:    LDC  3,10(6)	load size of array z
 59:     ST  3,-2(1)	save size of array z
* EXPRESSION
 60:    LDC  3,3(6)	Load integer constant 
 61:     ST  3,-12(1)	Save index 
 62:    LDC  3,445(6)	Load integer constant 
 63:     LD  4,-12(1)	Restore index 
 64:    LDA  5,-3(1)	Load address of base of array z
 65:    SUB  5,5,4	Compute offset of value 
 66:     ST  3,0(5)	Store variable z
* EXPRESSION
*                       Begin call to  output
 67:     ST  1,-12(1)	Store old fp in ghost frame 
*                       Load param 1
* EXPRESSION
*                       Begin call to  cat
 68:     ST  1,-14(1)	Store old fp in ghost frame 
*                       Load param 1
 69:    LDA  3,-3(1)	Load address of base of array z
 70:     ST  3,-17(1)	Store parameter 
*                       Jump to cat
 71:    LDA  1,-14(1)	Load address of new frame 
 72:    LDA  3,1(7)	Return address in ac 
 73:    LDA  7,-32(7)	CALL cat
 74:    LDA  3,0(2)	Save the result in ac 
*                       End call to cat
 75:     ST  3,-15(1)	Store parameter 
*                       Jump to output
 76:    LDA  1,-12(1)	Load address of new frame 
 77:    LDA  3,1(7)	Return address in ac 
 78:    LDA  7,-73(7)	CALL output
 79:    LDA  3,0(2)	Save the result in ac 
*                       End call to output
* END COMPOUND
* Add standard closing in case there is no return statement
 80:    LDC  2,0(6)	Set return value to 0 
 81:     LD  3,-1(1)	Load return address 
 82:     LD  1,0(1)	Adjust fp 
 83:    LDA  7,0(3)	Return 
* END FUNCTION main
  0:    LDA  7,83(7)	Jump to init [backpatch] 
* INIT
 84:     LD  0,0(0)	Set the global pointer 
 85:    LDA  1,0(0)	set first frame at end of globals 
 86:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
 87:    LDA  3,1(7)	Return address in ac 
 88:    LDA  7,-32(7)	Jump to main 
 89:   HALT  0,0,0	DONE! 
* END INIT
