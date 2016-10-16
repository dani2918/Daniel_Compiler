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
int enteredFunc = 0;
bool funcFlag = false;
bool leaveFlag;

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


void scopeAndTypeR(TreeNode * t)
{

	if (t == NULL)
		return;

	scopeAndType(t);

	//Unlinke in printtree.cpp, we'll process children in the function below
	scopeAndTypeR(t->sibling);

}

void scopeAndType(TreeNode * t)
{
	bool alreadyInTable = true;
	char * s; 

		if(t != NULL)
		{
			switch (t -> nodekind)
			{
			// if we have a declaration
				case DeclK:
				printf("inserting: %s \n", t->attr.name );
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
							printf("Func enter %s \n", t->attr.name);
							symTab.enter(t->attr.name);
							funcFlag = true;
							for (int i = 0; i < 3; i++)
							{
								if (t->child[i] != NULL)
									{
										scopeAndTypeR(t->child[i]);
									}

							}
							symTab.print(pointerPrintStr);
							printf("Leaving\n");
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
									default:
										break;
								}
							break;

						case recDeclaration:
							// printf("Record %s ", t->attr.name);
							break;

						case paramDeclaration:
							//printf("Param %s ", t->attr.name);

							//alreadyInTable = symTab.insert(t->attr.name, (TreeNode *) t);
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
					if (t->kind.stmt != compoundStmt)
					{
						alreadyInTable = symTab.insert(t->attr.name, (TreeNode *) t);
					}
					//print stmt kind
					switch(t->kind.stmt)
					{
						case compoundStmt:
							if (!funcFlag)
							{	
								symTab.enter("Compound Statement");
								for (int i = 0; i < 3; i++)
								{
									if (t->child[i] != NULL)
										{
											scopeAndTypeR(t->child[i]);
										}
								}
								symTab.print(pointerPrintStr);
								printf("Leaving compound\n");
								symTab.leave();
							}
							else
							{
								funcFlag = false;
								for (int i = 0; i < 3; i++)
								{
									if (t->child[i] != NULL)
										{
											scopeAndTypeR(t->child[i]);
										}
								}
								symTab.print(pointerPrintStr);
							}

							

								
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

		printf("we're at %s\n", t->attr.name );

	}