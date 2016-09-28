/*
Matthew Daniel
syntaxTree.h
September 20, 2016
*/

#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H
enum childSib
{
	non, chi, sib
};


//int printFormatting(TreeNode * t, int sibCount, int childCount, childSib cs);
void printTree(TreeNode * t);
int countChildren(TreeNode * t);
void printFormat(int sibCount, int childCount, childSib cs);
void printTreeR(TreeNode * t, int sibCount, int childCount, childSib cs);
void printTree(TreeNode * t, int sibCount, int childCount, childSib cs);

//TreeNode * newTestNode();

TreeNode * newDeclNode(DeclKind kind);

TreeNode * newStmtNode(StmtKind kind);

TreeNode * newExpNode(ExpKind kind);





#endif