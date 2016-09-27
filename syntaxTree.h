/*
Matthew Daniel
syntaxTree.h
September 20, 2016
*/

#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H


void printTree(TreeNode * t);

//TreeNode * newTestNode();

TreeNode * newDeclNode(DeclKind kind);

TreeNode * newStmtNode(StmtKind kind);

TreeNode * newExpNode(ExpKind kind);





#endif