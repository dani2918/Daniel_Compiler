/* 	Matthew Daniel
	semantic.h

*/ 

#ifndef SEMANTIC_H
#define SEMANTIC_H


void scopeAndType(TreeNode * t);
int countChildren(TreeNode * t);
void scopeAndTypeR(TreeNode * t, int sibCount, int childCount, childSib cs);
void scopeAndType(TreeNode * t, int sibCount, int childCount, childSib cs);
SymbolTable getSymTab();


#endif