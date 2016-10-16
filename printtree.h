/* 	Matthew Daniel
	printtree.h

*/ 


#ifndef PRINTTREE_H
#define PRINTTREE_H


//int printFormatting(TreeNode * t, int sibCount, int childCount, childSib cs);
void printTree(TreeNode * t, bool cp);
int countChildren(TreeNode * t);
void printFormat(int sibCount, int childCount, childSib cs);
void printTreeR(TreeNode * t, int sibCount, int childCount, childSib cs);
void printTree(TreeNode * t, int sibCount, int childCount, childSib cs);



#endif