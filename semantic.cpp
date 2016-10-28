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
#include "typeCheck.h"


SymbolTable symTab;
int enteredFunc = 0;
bool funcFlag = false;
bool leaveFlag;
bool defnErr = false;
int checkCount = 0;

// for when we need to lookup, get pointers from symTab
TreeNode * originalDecl;
TreeNode * lhs;
TreeNode * rhs;
TreeNode * namecheck;

SymbolTable getSymTab()
{
	return symTab;
}

void scopeAndTypeR(TreeNode * t)
{

	if (t == NULL)
		return;
	//Unlinke in printtree.cpp, I'll process children in the function below
	scopeAndType(t);

	
	//If we initialize a var to iteself with a colon, throw an error, give node type undefined
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

				// Add to table if we can
				alreadyInTable = symTab.insert(t->attr.name, (TreeNode *) t);
				if(alreadyInTable == false) 
				{
					originalDecl = (TreeNode *)symTab.lookup(t->attr.name);
					printError(10, t->lineno, t->attr.name, originalDecl->lineno, na, na);
				}

				
				//Switch types of declarations

					switch (t->kind.decl)
					{

						case varDeclaration:

						// If we have x:x attempted init, throw an error
						// if (t-> child[0] != NULL && t->child[0] -> kind.exp == IdK)
						// {
						// 	if (strcmp(t->attr.name, t->child[0]->attr.name) == 0)
						// 	{
						// 		printError(11, t->lineno, t->attr.name, 0, na, na);
						// 		t->type = undefined;
						// 	}

						// }
						defnErr = false;
						checkCount = 0;
						if (t->child[0] != NULL)
						{
							checkDefnErr(t, t, defnErr, checkCount);
						}

						if (defnErr == true)
						{
							printError(11, t->lineno, t->attr.name, 0, na, na);
							t->type = undefined;
						}

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
							t-> isFun = true;
							funcFlag = true;
							for (int i = 0; i < 3; i++)
							{
								if (t->child[i] != NULL)
								{
									scopeAndTypeR(t->child[i]);
								}

							}
							symTab.leave();

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
										break;
									case boolean:
										break;
									case character:
										break;	
									case record:
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
							}
			
							break;
						case returnStmt:
							if (t->child[0] != NULL)
							{
								scopeAndTypeR(t->child[0]);
								originalDecl = t->child[0];
								if(originalDecl -> isArray == true)
								{
									printError(8, t->lineno, NULL, 0, na, na);
								}
							}
							break;
						case selectionStmt:
							for (int i = 0; i < 3; i++)
							{
								if (t->child[i] != NULL)
								{
									scopeAndTypeR(t->child[i]);
								}
							}
							break;
						case iterationStmt:
							for (int i = 0; i < 3; i++)
							{
								if (t->child[i] != NULL)
								{
									scopeAndTypeR(t->child[i]);
								}
							}
							break;
						case breakStmt:
							// printf("Break ");
							break;
						default:
							break;
					}
					break;

				case ExpK:
					bool isArrayLHS, isArrayRHS, isBinaryOp, isFunLHS, isFunRHS;
					ExpType lhsType, rhsType;
					bool lhsCheck, rhsCheck, mismatch;
					ExpType wrongLHS, wrongRHS, operandType;
					int arrayError;
					bool opErr; 



					isArrayLHS = isArrayRHS = isBinaryOp = false;
					switch(t->kind.exp)
					{
						case IdK:
							//If symbol not defined
							originalDecl = (TreeNode *)symTab.lookup(t->attr.name);
							if (originalDecl == NULL)
							{
								printError(11, t->lineno, t->attr.name, 0, na, na);
								t->type = undefined;
								//t->isArray = false;
							}
							else
							{
								//resetting information to appropriate values
								t-> type = originalDecl -> type;
								t -> isArray = originalDecl -> isArray;
								t -> isStatic = originalDecl -> isStatic;
							}


							//issue error if trying to use function as variable
							if (originalDecl != NULL && originalDecl -> kind.decl == funDeclaration)
							{
								printError(9, t->lineno, t->attr.name, 0, na, na);
								t -> type = undefined;
							}

							if(t->child[0] != NULL)
							{
								scopeAndTypeR(t->child[0]);
								// the id has children, but is not an array
								if(t->isArray == false)
								{
									printError(6, t->lineno, t->attr.name, 0, na, na);
								}
							}
					
							break;

						//process these two together
						case AssK:
						case OpK:
						lhsCheck = rhsCheck = true;
						mismatch = isFunLHS = isFunRHS = false;
						wrongLHS = wrongRHS = undefined;
						arrayError = 0;
						opErr = false;
						operandType = undefined;

							for(int i = 0; i < 3; i++) 
							{
								scopeAndTypeR(t->child[i]);
							}
							lhs = rhs = NULL;
							if (t->child[0] != NULL)
							{
								lhs = t->child[0];
								lhsType = lhs -> type;
								isArrayLHS = lhs -> isArray;
								isFunLHS = lhs -> isFun;
							}
							if (t->child[1] != NULL)
							{
								rhs = t->child[1];
								rhsType = rhs -> type;
								isArrayRHS = rhs -> isArray;
								isBinaryOp = true;
								isFunRHS = rhs -> isFun;
							}
							
							// Calls type checking functions on both unary and binary ops
							if (rhs == NULL)
							{
								checkTypes(t, t->attr.name, lhs, rhs, lhsCheck, mismatch, wrongLHS, wrongRHS, isArrayLHS, arrayError, operandType, isFunLHS);
							}
							else
							{
								checkTypes(t, t->attr.name, lhs, rhs, lhsCheck, rhsCheck, mismatch, wrongLHS, wrongRHS, isArrayLHS, isArrayRHS, arrayError, operandType, isFunLHS, isFunRHS);
							}


							//Print appropriate errors
								if(!lhsCheck && lhsType != undefined)
								{
									// print unary error
									if (rhs == NULL)
									{
										printError(14, t->lineno, t->attr.name, 0, operandType, wrongLHS);
									}
									else
									{
										printError(1, t->lineno, t->attr.name, 0, operandType, wrongLHS);
									}	
									opErr = true;
								}
								if(!rhsCheck && rhsType != undefined)
								{
									printError(2, t->lineno, t->attr.name, 0, operandType, wrongRHS);
									opErr = true;
								}
								if(mismatch && !opErr)
								{
									printError(3, t->lineno, t->attr.name, 0, wrongLHS, wrongRHS);
								}

							switch (arrayError)
							{
								//Get an array when we shouldn't have
								case 1:
									printError(12, t->lineno, t->attr.name, 0, na, na);
									break;
								// Only works on arrays
								case 2:
									printError(13, t->lineno, t->attr.name, 0, na, na);
									break;
								//Cannot index named nonarray
								case 3:
									originalDecl = t->child[0];
									namecheck = (TreeNode *)symTab.lookup(t->child[0]->attr.name);
									//The name of the array does exist, check to see if there is
									// even a symbol defined
									if (originalDecl != NULL)
									{
										if (namecheck != NULL || t->child[0]-> kind.exp == IdK)
										{
											printError(6, t->lineno, originalDecl->attr.name, 0, na, na);
										}
										else
										{
											printError(7, t->lineno, originalDecl->attr.name, 0, na, na);
										}
									}

									break;
								//Indexed by nonint
								case 4: 
									originalDecl = t->child[0];
									printError(4, t->lineno, originalDecl->attr.name, 0, na, wrongRHS);
									break;
								case 5:
									originalDecl = t->child[1];
									printError(5, t->lineno, originalDecl->attr.name, 0, na, na);
									break;
								//Throw both errors 4 and 5
								case 45:
									originalDecl = t->child[0];
									printError(4, t->lineno, originalDecl->attr.name, 0, na, wrongRHS);
									originalDecl = t->child[1];
									printError(5, t->lineno, originalDecl->attr.name, 0, na, na);
									break;
								case 34:
									originalDecl = t->child[0];
									namecheck = (TreeNode *)symTab.lookup(t->child[0]->attr.name);
									//The name of the array does exist, check to see if there is
									// even a symbol defined
									if (originalDecl != NULL)
									{
										if (namecheck != NULL || t->child[0]->kind.exp == IdK)
										{
											printError(6, t->lineno, originalDecl->attr.name, 0, na, na);
										}
										else
										{
											printError(7, t->lineno, originalDecl->attr.name, 0, na, na);
										}
									}
									printError(4, t->lineno, originalDecl->attr.name, 0, na, wrongRHS);
									break;
								case 35:
									originalDecl = t->child[0];
									namecheck = (TreeNode *)symTab.lookup(t->child[0]->attr.name);
									//The name of the array does exist, check to see if there is
									// even a symbol defined
									if (originalDecl != NULL)
									{
										if (namecheck != NULL || t->child[0]-> kind.exp == IdK)
										{
											printError(6, t->lineno, originalDecl->attr.name, 0, na, na);
										}
										else
										{
											printError(7, t->lineno, originalDecl->attr.name, 0, na, na);
										}
									}
									originalDecl = t->child[1];
									printError(5, t->lineno, originalDecl->attr.name, 0, na, na);
									break;
								case 345:
									originalDecl = t->child[0];
									namecheck = (TreeNode *)symTab.lookup(t->child[0]->attr.name);
									if (originalDecl != NULL)
									{
										if (namecheck != NULL || t->child[0]-> kind.exp == IdK)
										{
											printError(6, t->lineno, originalDecl->attr.name, 0, na, na);
										}
										else
										{
											printError(7, t->lineno, originalDecl->attr.name, 0, na, na);
										}
									}
									printError(4, t->lineno, originalDecl->attr.name, 0, na, wrongRHS);
									originalDecl = t->child[1];
									printError(5, t->lineno, originalDecl->attr.name, 0, na, na);
									break;
								default: 
									break;
							}

							break;


						case constK:
							for(int i = 0; i < 3; i++) 
							{
								scopeAndTypeR(t->child[i]);
							}
							break;

						case CallK:
							originalDecl = (TreeNode *)symTab.lookup(t->attr.name);
							// if not, throw non exist error
							if (originalDecl == NULL)
							{
								printError(11, t->lineno, t->attr.name, 0, na, na);
								t->type = undefined;
								//t->isArray = false;
							} 
							//if not a function, throw that error
							else 
							{
								t-> type = originalDecl -> type;
								t -> isArray = originalDecl -> isArray;
								t -> isStatic = originalDecl -> isStatic;
									
								if(originalDecl -> kind.decl != funDeclaration)
								{
									printError(0, t->lineno, t->attr.name, 0, na, na);
								}
							}
							for(int i = 0; i < 3; i++) 
							{
								scopeAndTypeR(t->child[i]);
							}

							break;

						default:
							break;
					}	

				default:
					break;
			}	
		}

	}


void printError(int errno, int errorLine, char * symbol, int redefline, ExpType right, ExpType wrong)
{
	char * wrongType;
	char * rightType;
	numErrors++;
	if (wrong != na || right != na)
	{
		switch (wrong)
		{
			case integer:
				wrongType =strdup("type int");
				break;
			case boolean:
				wrongType =strdup("type bool");
				break;
			case character: 
				wrongType =strdup("type char");
				break;
			case record: 
				wrongType =strdup("type rec");
				break;
			case Void:
				wrongType =strdup("type void");
				break;
			case undefined:
				wrongType =strdup("type undefined");
			case charint:
				wrongType = strdup("type char or type int");
			case nonvoid:
				wrongType = strdup("NONVOID");
				break;
			default:
				break;
		}
		switch (right)
		{
			case integer:
				rightType =strdup("type int");
				break;
			case boolean:
				rightType =strdup("type bool");
				break;
			case character: 
				rightType =strdup("type char");
				break;
			case record: 
				rightType =strdup("type rec");
				break;
			case Void:
				rightType =strdup("type void");
				break;
			case undefined:
				rightType =strdup("type undefined");
				break;
			case charint:
				rightType = strdup("type char or type int");
				break;
			case nonvoid:
				rightType = strdup("NONVOID");
			default:
				break;
		}
	}

	switch (errno)
	{
		case -2:
			printf("ERROR(LINKER): Procedure main is not defined.\n");
			break;
		case -1:
			printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", symbol);
			exit(-1);
		case 0:
			printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", errorLine, symbol);
			break;
		case 1:
			printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", errorLine, symbol, rightType, wrongType);
			break;
		// case -3: 
		// 	printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given %s.\n", errorLine, symbol, rightType, wrongType);
		// 	break;
		case 2:
			printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n", errorLine, symbol, rightType, wrongType);
			break;
		case 3:
			printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", errorLine, symbol, rightType, wrongType);
			break;
		case 4:
			printf("ERROR(%d): Array '%s' should be indexed by type int but got %s.\n", errorLine, symbol, wrongType);
			break;
		case 5:
			printf("ERROR(%d): Array index is the unindexed array '%s'.\n", errorLine, symbol);
			break;
		case 6:
			printf("ERROR(%d): Cannot index nonarray '%s'.\n", errorLine, symbol);
			break;
		case 7:
			printf("ERROR(%d): Cannot index nonarray.\n", errorLine);
			break;
		case 8:
			printf("ERROR(%d): Cannot return an array.\n", errorLine);
			break;
		case 9:
			printf("ERROR(%d): Cannot use function '%s' as a variable.\n", errorLine, symbol);
			break;
		case 10:
			printf("ERROR(%d): Symbol '%s' is already defined at line %d.\n", errorLine, symbol, redefline);
			break;
		case 11:
			printf("ERROR(%d): Symbol '%s' is not defined.\n", errorLine, symbol);
			break;
		case 12:
			printf("ERROR(%d): The operation '%s' does not work with arrays.\n", errorLine, symbol);
			break;
		case 13:
			printf("ERROR(%d): The operation '%s' only works with arrays.\n", errorLine, symbol);
			break;
		case 14:
			printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given %s.\n", errorLine, symbol, rightType, wrongType);
			break;
		
		default:	
			printf("ERROR(%d): Undefined error\n", errorLine);
			break;
	}
}


void checkDefnErr(TreeNode * t, TreeNode * checkNode, bool &foundError, int &checkCount)
{
	TreeNode * lookup;

	if (checkNode == NULL)
	{
		return;
	}

	//printf("Check node is: %s \n", checkNode -> attr.name);

	lookup = (TreeNode *)symTab.lookup(checkNode->attr.name);
	checkCount++;

	//If we aren't on the original node
	if(checkCount != 1)
	{
		if(lookup == t)
		{
			//printf("found a match!: %s\n", checkNode->attr.name);
			foundError = true;
		}
	}


	//printf("got here!!\n");
	if (checkNode -> child[0] != NULL && checkNode->child[0] -> kind.exp == IdK)
	{
		//printf("got here!! child 0 is: %s\n");
		checkDefnErr(t, checkNode->child[0], defnErr, checkCount);
	}
	if (checkNode -> child[1] != NULL && checkNode->child[1] -> kind.exp == IdK)
	{
		//printf("got here!! child 1\n");
		checkDefnErr(t, checkNode->child[1], defnErr, checkCount);
	}

}


