/*
Matthew Daniel
syntaxTree.h
September 20, 2016
*/

#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

TreeNode * newDeclNode(DeclKind kind);
TreeNode * newStmtNode(StmtKind kind);
TreeNode * newExpNode(ExpKind kind);
TreeNode * newExpTypeNode();


#endif