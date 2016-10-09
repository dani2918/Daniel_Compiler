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




TreeNode * newDeclNode(DeclKind kind)
{
	TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;

	// Check from util.c code
	if (t==NULL)
    printf("Out of memory error at line %d\n",lineno);

  	else 
  	{
	    for (i=0;i<MAXCHILDREN;i++) 
	    	{
	    		t->child[i] = NULL;
	    	}
	    t->sibling = NULL;
	    t->nodekind = DeclK;
	    t->kind.decl = kind;
	    t->lineno = lineno;
  	}
		
	return t;
}

TreeNode * newStmtNode(StmtKind kind)
{
	TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;

	// Check from util.c code
	if (t==NULL)
    printf("Out of memory error at line %d\n",lineno);
  	else 
  	{
	    for (i=0;i<MAXCHILDREN;i++) 
	    	{
	    		t->child[i] = NULL;
	    	}
	    t->sibling = NULL;
	    t->nodekind = StmtK;
	    t->kind.stmt = kind; 
	    t->lineno = lineno;
  	}
		
	return t;
}


TreeNode * newExpNode(ExpKind kind)
{
	TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;

	// Check from util.c code
	if (t==NULL)
    printf("Out of memory error at line %d\n",lineno);
  	else 
  	{
	    for (i=0;i<MAXCHILDREN;i++) 
	    	{
	    		t->child[i] = NULL;
	    	}
	    t->sibling = NULL;
	    t->nodekind = ExpK;
	    t->kind.exp = kind;
	    t->lineno = lineno;

	   // t->type = integer;
  	}
		
	return t;
}

TreeNode * newExpTypeNode()
{
	TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;

	// Check from util.c code
	if (t==NULL)
    printf("Out of memory error at line %d\n",lineno);
  	else 
  	{
	    for (i=0;i<MAXCHILDREN;i++) 
	    	{
	    		t->child[i] = NULL;
	    	}
	    t->sibling = NULL;
	    t->nodekind = ExpK;
	    t->lineno = lineno;
	    //t->type = type;
  	}
		
	return t;
}

