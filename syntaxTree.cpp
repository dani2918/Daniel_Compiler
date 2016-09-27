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

int sibCount = 0;
int childCount = 0;

void printTree(TreeNode * t)
{
	printTree(t, 0, 0);
}

void printTree(TreeNode * t, int sibCount, int childCount)
{
	

	const char * arrMsg = "is array ";
	const char * arrMsgToggle; 
	TreeNode * orig = t;

		if(t != NULL)
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
							if(t-> isArray == true)
									{
										arrMsgToggle = arrMsg;
									}
									else
									{
										arrMsgToggle = "";
									}
								// switch types
								switch (t->type)
								{
									
									case integer:
										printf("%sof type int ", arrMsgToggle);
										break;
									case boolean:
										printf("%sof type bool ", arrMsgToggle);
										break;
									case character:
										printf("%sof type char ", arrMsgToggle);
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
			if(t -> sibling != NULL)
			{
				printf("Sibling: %d  ", sibCount);
			}
			
			printTree(t-> sibling, ++sibCount, childCount);

			if (t-> child[childCount] != NULL)
			{
				int newChildCount = childCount++;
				printTree(t->child[childCount], 0, newChildCount);
			}
		}
	
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


