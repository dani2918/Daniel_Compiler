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
	int sibCount = 0;
	int childCount = 0;
	do
	{
		//printf("Times through: %d\n", i);
		switch (t -> nodekind)
		{
	
			// if we have a declaration
			case DeclK:
				//printf("Declaration!\n" );

				//Switch types of declarations
				switch (t->kind.decl)
				{
					case varDeclaration:
						printf("Var %s ", t->attr.name);

							// switch types
							switch (t->type)
							{
								case integer:
									printf("of type int ");
									break;
								case boolean:
									printf("of type bool ");
									break;
								case character:
									printf("of type char ");
									break;	
							}

						break;
					case funDeclaration:
						break;
					case recDeclaration:
						break;
				}
				
				break;
			default:
				break;
		
		}
		printf("[line: %d]\n", t->lineno );
		t = t -> sibling;
		if(t != NULL)
		{
			printf("Sibling: %d  ", sibCount);
		}
		sibCount++;
	} while (t != NULL);
	
}

// TreeNode * newTestNode()
// {
// 	TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
// 	t -> sibling = NULL;
// 	return t;
// }

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
	    t->type = integer;
  	}
		
	return t;
}


