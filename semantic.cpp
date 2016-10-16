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

// for when we need to lookup, get pointers from symTab
TreeNode * originalDecl;
TreeNode * lhs;
TreeNode * rhs;

SymbolTable getSymTab()
{
	return symTab;
}

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
				//printf("inserting: %s \n", t->attr.name );
				alreadyInTable = symTab.insert(t->attr.name, (TreeNode *) t);

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
						//	printf("Func enter %s \n", t->attr.name);
							symTab.enter(t->attr.name);
							funcFlag = true;
							for (int i = 0; i < 3; i++)
							{
								if (t->child[i] != NULL)
									{
										scopeAndTypeR(t->child[i]);
									}

							}
							//symTab.print(pointerPrintStr);
							//printf("Leaving\n");
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
					// if (t->kind.stmt != compoundStmt)
					// {
					// 	alreadyInTable = symTab.insert(t->attr.name, (TreeNode *) t);
					// }
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
								//symTab.print(pointerPrintStr);
								//printf("Leaving compound\n");
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
								//symTab.print(pointerPrintStr);
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
					bool isArrayLHS, isArrayRHS, isBinaryOp;
					ExpType lhsType, rhsType;

					isArrayLHS = isArrayRHS = isBinaryOp = false;
					// originalDecl = (TreeNode *)symTab.lookup(t->child[0]->attr.name);
					// 		if (originalDecl == NULL)
					// 		{
					// 			printError(11, lineno, t->child[0]->attr.name, 0);
					// 		}
					switch(t->kind.exp)
					{
						case IdK:
							originalDecl = (TreeNode *)symTab.lookup(t->attr.name);
							if (originalDecl == NULL)
							{
								printError(11, t->lineno, t->attr.name, 0);
							}
							if(t-> isArray == true)
								{
									// arrMsgToggle = arrMsg;
								}
								else
								{
									// arrMsgToggle = "";
								}
							break;

						//process these two together?
						case OpK:
						case AssK:

							for(int i = 0; i < 3; i++) 
							{
								scopeAndTypeR(t->child[i]);
							}
							if (t->child[0] != NULL)
							{
								lhs = t->child[0];
								lhsType = lhs -> type;
								isArrayLHS = lhs -> isArray;
							}
							if (t->child[1] != NULL)
							{
								rhs = t->child[1];
								rhsType = rhs -> type;
								isArrayRHS = rhs -> isArray;
								isBinaryOp = true;
							}
							//printf("got here\n");
							// lookup, see if it is function
							// if (lhs != NULL)
							// {
							// 	originalDecl = (TreeNode *)symTab.lookup(lhs->attr.name);
							// 	printf("lhs->attrname is: %s\n", lhs->attr.name);
							// }
							
							//printf("got here2\n");
							// if not, throw error 0
							if (originalDecl == NULL)
							{
								//printf("t->attr.name is: %s\n", t->attr.name);
							//printf("t->lineno is: %d\n", t->lineno);

								// if (isBinaryOp)
								// {
								// 	printError(11, t->lineno, t->attr.name, 0);
								// }
								// else
								// {
								// 	printError(11, t->lineno, t->attr.name, 0);
								// }
								//printf("got here3\n");
							}

							break;

						
							
							// printf("Assign: %s ", t-> attr.name);
						//	break;

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
							for(int i = 0; i < 3; i++) 
							{
								scopeAndTypeR(t->child[i]);
							}
							// lookup, see if it is function
							originalDecl = (TreeNode *)symTab.lookup(t->attr.name);
							// if not, throw error 0
							if (originalDecl == NULL || originalDecl -> kind.decl != funDeclaration)
							{
								printError(0, t->lineno, t->attr.name, 0);
							}
							
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
				originalDecl = (TreeNode *)symTab.lookup(t->attr.name);
				printError(10, t->lineno, t->attr.name, originalDecl->lineno);
			}
			
		}

		//printf("we're at %s\n", t->attr.name );

	}


	void printError(int errno, int errorLine, char * symbol, int redefline)
	{
		numErrors++;
		switch (errno)
		{
			case 0:
				printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", errorLine, symbol);
				break;
			case 1:
				printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", errorLine, symbol, "", "");
				break;
			case 2:
				printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n", errorLine, symbol, "", "");
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				printf("ERROR(%d): Symbol '%s' is already defined at line %d.\n", errorLine, symbol, redefline);
				break;
			case 11:
				printf("ERROR(%d): Symbol '%s' is not defined.\n", errorLine, symbol);
				break;
			case 12:
				break;
			case 13:
				break;
			case 14:
				break;
			default:	
				printf("ERROR(%d): Undefined error\n", errorLine);
				break;
		}
	}