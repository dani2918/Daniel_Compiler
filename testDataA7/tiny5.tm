* C- compiler version C-F16
* Built: Nov 13, 2016
* Author: Robert B. Heckendorn
* File compiled:  tiny5.c-
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
* FUNCTION wolf
 42:     ST  3,-1(1)	Store return address. 
* COMPOUND
 43:    LDC  3,2(6)	load size of array w
 44:     ST  3,-3(1)	save size of array w
* Compound Body
* RETURN
 45:    LDC  3,77(6)	Load integer constant 
 46:     ST  3,-6(1)	Save left side 
 47:     LD  3,-2(1)	Load address of base of array garion
 48:     ST  3,-7(1)	Save left side 
 49:    LDC  3,1(6)	Load integer constant 
 50:     LD  4,-7(1)	Load left into ac1 
 51:    SUB  3,4,3	compute location from index 
 52:     LD  3,0(3)	Load array element 
 53:     LD  4,-6(1)	Load left into ac1 
 54:    ADD  3,4,3	Op + 
 55:    LDA  2,0(3)	Copy result to rt register 
 56:     LD  3,-1(1)	Load return address 
 57:     LD  1,0(1)	Adjust fp 
 58:    LDA  7,0(3)	Return 
* END COMPOUND
* Add standard closing in case there is no return statement
 59:    LDC  2,0(6)	Set return value to 0 
 60:     LD  3,-1(1)	Load return address 
 61:     LD  1,0(1)	Adjust fp 
 62:    LDA  7,0(3)	Return 
* END FUNCTION wolf
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
 63:     ST  3,-1(1)	Store return address. 
* COMPOUND
 64:    LDC  3,3(6)	load size of array y
 65:     ST  3,-2(1)	save size of array y
* Compound Body
* EXPRESSION
 66:    LDC  3,1(6)	Load integer constant 
 67:     ST  3,-6(1)	Save index 
 68:    LDC  3,666(6)	Load integer constant 
 69:     LD  4,-6(1)	Restore index 
 70:    LDA  5,-3(1)	Load address of base of array y
 71:    SUB  5,5,4	Compute offset of value 
 72:     ST  3,0(5)	Store variable y
* EXPRESSION
*                       Begin call to  wolf
 73:     ST  1,-6(1)	Store old fp in ghost frame 
*                       Load param 1
 74:    LDA  3,-3(1)	Load address of base of array y
 75:     ST  3,-8(1)	Store parameter 
*                       Jump to wolf
 76:    LDA  1,-6(1)	Load address of new frame 
 77:    LDA  3,1(7)	Return address in ac 
 78:    LDA  7,-37(7)	CALL wolf
 79:    LDA  3,0(2)	Save the result in ac 
*                       End call to wolf
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
 85:    LDA  1,-4(0)	set first frame at end of globals 
 86:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
 87:    LDC  3,3(6)	load size of array g
 88:     ST  3,0(0)	save size of array g
* END INIT GLOBALS AND STATICS
 89:    LDA  3,1(7)	Return address in ac 
 90:    LDA  7,-28(7)	Jump to main 
 91:   HALT  0,0,0	DONE! 
* END INIT
