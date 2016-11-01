/* 	Matthew Daniel
	typeCheck.h

*/ 

#ifndef TYPECHECK_H
#define TYPECHECK_H

void checkTypes(TreeNode * t, char * name, TreeNode * right, TreeNode * left, bool &leftGood, bool &rightGood, bool &mismatch, ExpType &wrongLHS, ExpType &wrongRHS, bool &isArrayLHS, bool &isArrayRHS, int &arrayError, ExpType &operandType, bool isFunLHS, bool isFunRHS);
void checkTypes(TreeNode * t, char * name, TreeNode * right, TreeNode * left, bool &leftGood, bool &mismatch, ExpType &wrongLHS,  ExpType &wrongRHS, bool &isArrayLHS, int &arrayError, ExpType &operandType, bool isFunLHS);

void checkParams(TreeNode * t, TreeNode * originalDecl);
#endif