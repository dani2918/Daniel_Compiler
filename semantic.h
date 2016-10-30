/* 	Matthew Daniel
	semantic.h

*/ 

#ifndef SEMANTIC_H
#define SEMANTIC_H


int countChildren(TreeNode * t);
void setup(TreeNode * t);
void scopeAndTypeR(TreeNode * t);
void scopeAndType(TreeNode * t);

void printError(int errno, int errorLine, char * symbol, int redefline, ExpType right, ExpType wrong);


SymbolTable getSymTab(int errno, int errorLine, char * symbol, int redefline);

void checkDefnErr(TreeNode * t, TreeNode * checkNode, bool &foundError, int &checkCount);


#endif