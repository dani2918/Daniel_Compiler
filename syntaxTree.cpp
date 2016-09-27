/*
Matthew Daniel
syntaxTree.cpp
September 20, 2016
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "globals.h"
#include "syntaxTree.h"


void printTree(TreeNode * t)
{
	
}

TreeNode * newTestNode()
{
	TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
	t -> sibling = NULL;
	return t;
}

TreeNode * newDeclNode()
{
	TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
	
		
	return t;
}