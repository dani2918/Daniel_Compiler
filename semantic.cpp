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
bool returnFlag = false;
TreeNode * returnCheck;

// for when we need to lookup, get pointers from symTab
TreeNode * originalDecl;
TreeNode * lhs;
TreeNode * rhs;
TreeNode * namecheck;

SymbolTable getSymTab()
{
	return symTab;
}


//Set up I/O 
void setup(TreeNode * t)
{
	std::string input, output, inputb, outputb, inputc, outputc, outnl; 
	output = "output";
	outputb = "outputb";
	outputc = "outputc";
	input = "input";
	inputb = "inputb";
	inputc = "inputc";
	outnl = "outnl";

	//input
	t = newDeclNode(funDeclaration);
	t -> lineno = -1;
	t -> attr.name = strdup(input.c_str());
	t -> numChildren = 2;
	t -> type = integer;
	//t = t -> sibling;
	printf("GOT HERE\n");

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
							
							returnCheck = t;
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

							if (t->type != Void)
							{
								if (returnFlag == false)
								{
									printError(16, t->lineno, t->attr.name, 0, t->type, na);
								}

							}

							returnFlag = false;
							symTab.leave();

							returnCheck = NULL;
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
							returnFlag = true;
							if (t->child[0] != NULL)
							{
								scopeAndTypeR(t->child[0]);
								originalDecl = t->child[0];
								if(originalDecl -> isArray == true)
								{
									printError(8, t->lineno, NULL, 0, na, na);
								}
								if (returnCheck -> type != t -> child[0] -> type && t -> child[0] -> type != Void && returnCheck -> type != Void && returnCheck -> type != undefined && t -> child[0] -> type != undefined)
								{
									printError(17, t->lineno, returnCheck -> attr.name, returnCheck -> lineno, returnCheck -> type, t -> child[0] -> type);
								}
								if (returnCheck -> type == Void && t -> child[0] -> type != Void && returnCheck -> type != undefined && t -> child[0] -> type != undefined)
								{
									printError(18, t->lineno, returnCheck -> attr.name, returnCheck -> lineno, na, na);
								}
							}

							if (returnCheck -> type != Void && t -> child[0] == NULL)
							{
								printError(19, t->lineno, returnCheck -> attr.name, returnCheck -> lineno, returnCheck -> type, na);
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
							if (t->child[0] != NULL)
							{
								if (t->child[0]->type != boolean && t->child[0]->type != undefined)
								{
									printError(20, t->lineno, t->attr.name, 0, na, t->child[0]->type);
								}
								if(t->child[0]->isArray == true)
								{
									printError(21, t->lineno, t->attr.name, 0, na, na);
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
							if (t->child[0] != NULL)
							{
								if (t->child[0]->type != boolean && t->child[0]->type != undefined)
								{
									printError(20, t->lineno, t->attr.name, 0, na, t->child[0]->type);
								}
								if(t->child[0]->isArray == true)
								{
									printError(21, t->lineno, t->attr.name, 0, na, na);
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
							
							
							// If we have a binary op, check for array mismatching


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

							if(arrayError == 0 && isBinaryOp && lhsType != undefined && rhsType != undefined && ((isArrayRHS && !isArrayLHS) || (!isArrayRHS && isArrayLHS)))
							{
								std::string strName(t->attr.name);
								if(strName != "[")
								{
									printError(22, t->lineno, t->attr.name, 0, na, na);
								}
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
								printError(15, t->lineno, t->attr.name, 0, na, na);
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
		// System-like Errors ____________________________________________________________________________________________________________
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
		case 2:
			printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n", errorLine, symbol, rightType, wrongType);
			break;
		case 3:
			printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", errorLine, symbol, rightType, wrongType);
			break;

		// Array Errors ____________________________________________________________________________________________________________
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

		// Definiton Errors, operation errors ____________________________________________________________________________________

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
			printf("ERROR(%d): Unary '%s' requires an operand of %s but was given %s.\n", errorLine, symbol, rightType, wrongType);
			break;
		case 15:
			printf("ERROR(%d): Function '%s' is not defined.\n", errorLine, symbol);
			break;

		//Return Errors ____________________________________________________________________________________________________________
		case 16:
			printf("WARNING(%d): Expecting to return %s but function '%s' has no return statement.\n", errorLine, rightType, symbol);
			numErrors--;
			numWarnings++;
			break;	
		case 17:
			printf("ERROR(%d): Function '%s' at line %d is expecting to return %s but instead returns %s.\n", errorLine, symbol, redefline, rightType, wrongType );
			break;
		case 18:
			printf("ERROR(%d): Function '%s' at line %d is expecting no return value, but return has return value.\n", errorLine, symbol, redefline);
			break;
		case 19:
			printf("ERROR(%d): Function '%s' at line %d is expecting to return %s but return has no return value.\n", errorLine, symbol, redefline, rightType);
			break;

		// Boolean Test Errors ____________________________________________________________________________________________________________
		case 20:
			printf("ERROR(%d): Expecting Boolean test condition in %s statement but got %s.\n", errorLine, symbol, wrongType);
			break;
		case 21:
			printf("ERROR(%d): Cannot use array as test condition in %s statement.\n", errorLine, symbol);
			break;

		//  Binary op array check __________________________________________________________________________________________________________
		case 22:
			printf("ERROR(%d): '%s' requires that either both or neither operands be arrays.\n", errorLine, symbol);
			break;


		//  __________________________________________________________________________________________________________
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

	checkCount++;

	//If we aren't on the original node
	if(checkCount != 1)
	{
		// only look for nodes with ID
		if(checkNode -> kind.exp == IdK)
		{
			lookup = (TreeNode *)symTab.lookup(checkNode->attr.name);
		}
		if(lookup == t || lookup == NULL)
		{
			
			foundError = true;
			checkNode->type = undefined;
		}
	}

	if (checkNode -> child[0] != NULL )
	{
		//printf("got here!! child 0 is: %s\n");
		checkDefnErr(t, checkNode->child[0], defnErr, checkCount);
	}
	if (checkNode -> child[1] != NULL )
	{
		//printf("got here!! child 1\n");
		checkDefnErr(t, checkNode->child[1], defnErr, checkCount);
	}

}


