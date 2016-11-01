/* 	Matthew Daniel
	semantic.h

*/ 

#ifndef SEMANTIC_H
#define SEMANTIC_H


int countChildren(TreeNode * t);
TreeNode * setup(TreeNode * t, TreeNode * oldTree);
void scopeAndTypeR(TreeNode * t);
void scopeAndType(TreeNode * t);

void printError(int errno, int errorLine, char * symbol, int redefline, ExpType right, ExpType wrong, int paramNo);


SymbolTable getSymTab(int errno, int errorLine, char * symbol, int redefline);

void checkDefnErr(TreeNode * t, TreeNode * checkNode, bool &foundError, int &checkCount);
void checkConst(TreeNode * t, TreeNode * checkNode, bool &defnErr);


#endif