/* 	Matthew Daniel
	semantic.cpp

*/ 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "globals.h"
#include "syntaxTree.h"
#include "semantic.h"
#include "printtree.h"
#include "symbolTable.h"


SymbolTable symTab;

SymbolTable getSymTab()
{
	return symTab;
}

// // TODO: May have to remove? Do we want NULL children?
// int countChildren(TreeNode * t)
// {
// 	int numChildren = 0;
// 	TreeNode * countChildren;
// 	while (countChildren != NULL)
// 	{
// 		countChildren = t->child[numChildren];
// 		numChildren++;
// 	}
// 	// subtract time we went through and got NULL
// 	numChildren--;

// 	return numChildren;
// }

// void printFormat(int sibCount, int childCount, childSib cs)
// {
// 		// Print the formatting
// 	for (int i = 0; i < indent; i++)
// 		{
// 			printf("!   ");
// 		}
// 	switch(cs)
// 	{
// 		case non:
// 			break;
// 		case sib:
// 			printf("Sibling: %d  ", sibCount-1);
// 			break;
// 		case chi:
// 			printf("Child: %d  ", childCount-1);
// 			break;
// 	}
// }

void scopeAndType(TreeNode * t)
{
	sibCount = 0;
	childCount = 0;
	indent = 0;

	scopeAndTypeR(t, 0, 0, non);


}

void scopeAndTypeR(TreeNode * t, int sibCount, int childCount, childSib cs)
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

	scopeAndType(t, sibCount, childCount, cs);

	for (int i = 0; i < t->numChildren; i++)
	{
		
		scopeAndTypeR(t->child[i], 0, i, chi);
		childCount++;
	}

	scopeAndTypeR(t->sibling, sibCount, childCount, sib);

}

void scopeAndType(TreeNode * t, int sibCount, int childCount, childSib cs)
{
	bool alreadyInTable = true;
	//printFormat(sibCount, childCount, cs);
	char * s; 

		if(t != NULL)
		{
			switch (t -> nodekind)
			{
			// if we have a declaration
				case DeclK:
				alreadyInTable = symTab.insert(t->attr.name, (TreeNode *) t);
				// if(alreadyInTable == true)
				// {
				// 	//Error something
				// 	break; //may only break out of if?
				// }

					//Switch types of declarations



					switch (t->kind.decl)
					{

						case varDeclaration:

							//Differentiate between var and param
								//printf("Var %s ", t->attr.name);

							if(t-> isArray == true)
									{
									//	arrMsgToggle = arrMsg;
									}
									else
									{
									//	arrMsgToggle = "";
									}

								// switch types
								switch (t->type)
								{
									
									case integer:
										//printf("%sof type int ", arrMsgToggle);
										break;
									case boolean:
										//printf("%sof type bool ", arrMsgToggle);
										break;
									case character:
										///printf("%sof type char ", arrMsgToggle);
										break;	
									case record:
										//printf("%sof type record ", arrMsgToggle);
										break;
									default:
										break;
								}

							break;

						case funDeclaration:
							//printf("Func %s ", t->attr.name);
							symTab.enter(t->attr.name);
							//printf("entering funDeclaration\n");
							symTab.leave();

							// Print return type
							switch (t->type)
								{
									case integer:
										//printf("returns type int ");
										break;
									case boolean:
										//printf("returns type bool ");
										break;
									case character:
										// printf("returns type char ");
										break;	
									case Void:
										// printf("returns type void ");
										break;	
									case record:
										// printf("%sof type record ", arrMsgToggle);
										break;
								}
							break;

						case recDeclaration:
							// printf("Record %s ", t->attr.name);
							break;

						case paramDeclaration:
							// printf("Param %s ", t->attr.name);
							if(t-> isArray == true)
									{
										// arrMsgToggle = arrMsg;
									}
									else
									{
										// arrMsgToggle = "";
									}
							switch (t->type)
								{
									
									case integer:
										// printf("%sof type int ", arrMsgToggle);
										break;
									case boolean:
										// printf("%sof type bool ", arrMsgToggle);
										break;
									case character:
										// printf("%sof type char ", arrMsgToggle);
										break;	
									case record:
										// printf("%sof type record ", arrMsgToggle);
										break;
									default:
										break;
								}

					}
					
					break;
				
				case StmtK:
					alreadyInTable = symTab.insert(t->attr.name, (TreeNode *) t);
					//print stmt kind
					switch(t->kind.stmt)
					{
						case compoundStmt:
							symTab.enter("Compound Statement");
							//printf("Compound ");
							break;
						case returnStmt:
							//printf("Return ");
							break;
						case selectionStmt:
							//printf("If ");
							break;
						case iterationStmt:
							//printf("While ");
							break;
						case breakStmt:
							// printf("Break ");
							break;
						default:
							break;
					}
					break;

				case ExpK:
					switch(t->kind.exp)
					{
						case IdK:
							// printf("Id: %s ", t->attr.name);
							if(t-> isArray == true)
								{
									// arrMsgToggle = arrMsg;
								}
								else
								{
									// arrMsgToggle = "";
								}
							break;

						
						case OpK:
							// printf("Op: %s ", t-> attr.name);
							break;

						case AssK:
							// printf("Assign: %s ", t-> attr.name);
							break;

						case constK:
							// printf("Const: ");
							switch(t -> type)
							{
								case boolean:
									if(t->attr.bvalue == true)
									{
										// printf("true ");
									}
									else
									{
										// printf("false ");
									}
									break;
								case integer:
									// printf("%d ", t->attr.value );
									break;
								case character:
									// printf("'%c' ", t->attr.cvalue );
									break;
								default:
									break;
							}
							break;

						case CallK:
							// printf("Call: %s ", t-> attr.name);
							break;

						default:
							break;
					}	

				default:
					break;
			}
			//print line number stored from scantype at time of making new node
			if(alreadyInTable == false) 
			{
				printf("%s already in symtab\n", t->attr.name);
			}
			
		}
	}