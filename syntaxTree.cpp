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

	//int numChildren = countChildren(t);
	// If we have children, increase the indent
	if (t->numChildren > 0)
	{
		indent++;
	}

	for (int i = 0; i < t->numChildren; i++)
	{
		
		printTreeR(t->child[i], 0, i, chi);
		childCount++;
	}

	// if we've printed children, unindent
	if(t->numChildren >0)
	{
		indent --;
	}
	printTreeR(t->sibling, sibCount, childCount, sib);

}

void printTree(TreeNode * t, int sibCount, int childCount, childSib cs)
{
	
	printFormat(sibCount, childCount, cs);


	const char * arrMsg = "is array ";
	const char * arrMsgToggle; 
	char * s; 

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
									case record:
										printf("%sof type record ", arrMsgToggle);
										break;
									default:
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
									case Void:
										printf("returns type void ");
										break;	
									case record:
										printf("%sof type record ", arrMsgToggle);
										break;
								}
							break;

						case recDeclaration:
							printf("Record %s ", t->attr.name);

							break;

						case paramDeclaration:
							printf("Param %s ", t->attr.name);
							if(t-> isArray == true)
									{
										arrMsgToggle = arrMsg;
									}
									else
									{
										arrMsgToggle = "";
									}
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
									case record:
										printf("%sof type record ", arrMsgToggle);
										break;
									default:
										break;
								}

					}
					
					break;
				
				case StmtK:
					switch(t->kind.stmt)
					{
						case compoundStmt:
							printf("Compound ");
							break;
						case returnStmt:
							printf("Return ");
							break;
						case selectionStmt:
							printf("If ");
							break;
						case iterationStmt:
							printf("While ");
							break;
						case breakStmt:
							printf("Break ");
							break;
						default:
							break;
					}
					break;

				case ExpK:
					switch(t->kind.exp)
					{
						case IdK:
							printf("Id: %s ", t->attr.name);
							if(t-> isArray == true)
								{
									arrMsgToggle = arrMsg;
								}
								else
								{
									arrMsgToggle = "";
								}
							break;
								// switch types
								// switch (t->type)
								// {
									
								// 	case integer:
								// 		printf("%sof type int ", arrMsgToggle);
								// 		break;
								// 	case boolean:
								// 		printf("%sof type bool ", arrMsgToggle);
								// 		break;
								// 	case character:
								// 		printf("%sof type char ", arrMsgToggle);
								// 		break;
								// 	case Void:
								// 		printf("%sof type void ", arrMsgToggle);
								// 		break;		
								// 	case record:
								// 		printf("%sof type record ", arrMsgToggle);
								// 		break;
								// }
							

						
						case OpK:
							printf("Op: %s ", t-> attr.name);
							break;

						case AssK:
							printf("Assign: %s ", t-> attr.name);
							break;

						case constK:
							printf("Const: ");
							switch(t -> type)
							{
								case boolean:
									if(t->attr.bvalue == true)
									{
										printf("true ");
									}
									else
									{
										printf("false ");
									}
									break;
								case integer:
									//printf("INTEGER\n");
									printf("%d ", t->attr.value );
									break;
								case character:
									printf("'%c' ", t->attr.cvalue );
									break;
								default:
									break;
							}
							break;

						case CallK:
							printf("Call: %s ", t-> attr.name);
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

