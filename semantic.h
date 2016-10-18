/* 	Matthew Daniel
	semantic.h

*/ 

#ifndef SEMANTIC_H
#define SEMANTIC_H


int countChildren(TreeNode * t);
void scopeAndTypeR(TreeNode * t);
void scopeAndType(TreeNode * t);

void printError(int errno, int errorLine, char * symbol, int redefline, ExpType right, ExpType wrong);

void checkTypes(TreeNode * t, char * name, TreeNode * right, TreeNode * left, bool &leftGood, bool &rightGood, ExpType &wrongLHS, ExpType &wrongRHS, bool &isArrayLHS, bool &isArrayRHS, int &arrayError);
void checkTypes(TreeNode * t, char * name, TreeNode * right, TreeNode * left, bool &leftGood, ExpType &wrongLHS, ExpType &wrongRHS, bool &isArrayLHS, int &arrayError);


SymbolTable getSymTab(int errno, int errorLine, char * symbol, int redefline);


#endif