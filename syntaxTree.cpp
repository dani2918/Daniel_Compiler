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

int sibCount;
int childCount;
int indent;
TreeNode * placeholder;


int countChildren(TreeNode * t)
{
	int numChildren = 0;
	TreeNode * countChildren;
	while (countChildren != NULL)
	{
		countChildren = t->child[numChildren];
		numChildren++;
	}
	// subtract time we went through and got NULL
	numChildren--;

	return numChildren;
}

void printFormat(int sibCount, int childCount, childSib cs)
{
		// Print the formatting
	for (int i = 0; i < indent; i++)
		{
			printf("!   ");
		}
	switch(cs)
	{
		case non:
			break;
		case sib:
			printf("Sibling: %d  ", sibCount-1);
			break;
		case chi:
			printf("Child: %d  ", childCount-1);
			break;
	}
}

void printTree(TreeNode * t)
{
	sibCount = 0;
	childCount = 0;
	indent = 0;

	printTreeR(t, 0, 0, non);


}

void printTreeR(TreeNode * t, int sibCount, int childCount, childSib cs)
{

	

	if (t == NULL)
		return;

	switch(cs)
	{
		case non:
			break;
		case sib:
			sibCount++;
			break;
		case chi:
			childCount++;
			break;
	}


	printTree(t, sibCount, childCount, cs);

	int numChildren = countChildren(t);
	// If we have children, increase the indent
	if (numChildren > 0)
	{
		indent++;
	}

	for (int i = 0; i < numChildren; i++)
	{
		printTreeR(t->child[i], 0, childCount, chi);
		childCount++;
	}
	printTreeR(t->sibling, sibCount, childCount, sib);

}

void printTree(TreeNode * t, int sibCount, int childCount, childSib cs)
{
	
	printFormat(sibCount, childCount, cs);


	const char * arrMsg = "is array ";
	const char * arrMsgToggle; 


		if(t != NULL)
		{
			switch (t -> nodekind)
			{
			// if we have a declaration
				case DeclK:
					//Switch types of declarations
					switch (t->kind.decl)
					{
						case varDeclaration:

							//Differentiate between var and param
							if (t-> isParam == true)
							{
								printf("Param %s ", t->attr.name);
							}
							else
							{
								printf("Var %s ", t->attr.name);
							}

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
							printf("Func %s ", t->attr.name);
							switch (t->type)
								{
									
									case integer:
										printf("returns type int ");
										break;
									case boolean:
										printf("returns type bool ");
										break;
									case character:
										printf("returns type char ");
										break;	
								}
							break;

						case recDeclaration:
							break;
					}
					
					break;
				
				case StmtK:
					switch(t->kind.stmt)
					{
						case compoundStmt:
							printf("Compound ");
							break;
						default:
							break;
					}


				default:
					break;
			}

			printf("[line: %d]\n", t->lineno );
			




			
		}
	
}


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
	    t->kind.stmt = kind; //printf("Kind is %d\n",kind );
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


