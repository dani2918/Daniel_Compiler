/* 	Matthew Daniel
	semantic.cpp

*/ 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <map>
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

	//Unlinke in printtree.cpp, I'll process children in the function below
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
				//printf("\ninserting: %s \n\n", t->attr.name );
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
							if (t->child[0] != NULL)
							{
								scopeAndTypeR(t->child[0]);
							}
							break;
						case iterationStmt:
							if (t->child[0] != NULL)
							{
								scopeAndTypeR(t->child[0]);
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
					bool isArrayLHS, isArrayRHS, isBinaryOp;
					ExpType lhsType, rhsType;
					bool lhsCheck, rhsCheck;
					ExpType wrongLHS, wrongRHS;
					int arrayError;



					isArrayLHS = isArrayRHS = isBinaryOp = false;
					// 		if (originalDecl == NULL)
					// 		{
					// 			printError(11, lineno, t->child[0]->attr.name, 0);
					// 		}
					switch(t->kind.exp)
					{
						case IdK:
							//printf("IdK string: %s\n", t->attr.name );
							originalDecl = (TreeNode *)symTab.lookup(t->attr.name);
							if (originalDecl == NULL)
							{
								printError(11, t->lineno, t->attr.name, 0, na, na);
								t->type = undefined;
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

						//process these two together?
						case AssK:
						case OpK:
						lhsCheck = rhsCheck = true;
						wrongLHS = wrongRHS = undefined;
						arrayError = 0;

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
							
							if (rhs == NULL)
							{
								checkTypes(t, t->attr.name, lhs, rhs, lhsCheck, wrongLHS, wrongRHS, isArrayLHS, arrayError);
							}
							else
							{
								checkTypes(t, t->attr.name, lhs, rhs, lhsCheck, rhsCheck, wrongLHS, wrongRHS, isArrayLHS, isArrayRHS, arrayError);
							}


							//Print appropriate errors
							if(!lhsCheck && lhsType != undefined)
							{
								printError(1, t->lineno, t->attr.name, 0, t->type, wrongLHS);
							}
							if(!rhsCheck && rhsType != undefined)
							{
								printError(2, t->lineno, t->attr.name, 0, t->type, wrongRHS);
							}

							//Get an array when we shouldn't have
							if(arrayError == 1)
							{
								printError(12, t->lineno, t->attr.name, 0, na, na);
							}

							//Don't get an array when we should have
							if(arrayError == 2)
							{
								printError(13, t->lineno, t->attr.name, 0, na, na);
							}
							break;

						
						//case AssK:
							// printf("Assign: %s ", t-> attr.name);
							//break;

						case constK:
							// printf("Const: ");
							for(int i = 0; i < 3; i++) 
							{
								scopeAndTypeR(t->child[i]);
							}
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
							// lookup, see if it exists
							originalDecl = (TreeNode *)symTab.lookup(t->attr.name);
							// if not, throw non exist error
							if (originalDecl == NULL)
							{
								printError(11, t->lineno, t->attr.name, 0, na, na);
								t->type = undefined;
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
							

							break;

						default:
							break;
					}	

				default:
					break;
			}

			if(alreadyInTable == false) 
			{
				originalDecl = (TreeNode *)symTab.lookup(t->attr.name);
				printError(10, t->lineno, t->attr.name, originalDecl->lineno, na, na);
			}
			
		}

		//printf("we're at %s\n", t->attr.name );

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
					wrongType =strdup("int");
					break;
				case boolean:
					wrongType =strdup("bool");
					break;
				case character: 
					wrongType =strdup("char");
					break;
				case record: 
					wrongType =strdup("rec");
					break;
				case Void:
					wrongType =strdup("void");
					break;
				case undefined:
					wrongType =strdup("undefined");
					break;
				default:
					break;
			}
			switch (right)
			{
				case integer:
					rightType =strdup("int");
					break;
				case boolean:
					rightType =strdup("bool");
					break;
				case character: 
					rightType =strdup("char");
					break;
				case record: 
					rightType =strdup("rec");
					break;
				case Void:
					rightType =strdup("void");
					break;
				case undefined:
					wrongType =strdup("undefined");
					break;
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
			case 2:
				printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n", errorLine, symbol, rightType, wrongType);
				break;
			case 3:
				printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", errorLine, symbol, rightType, wrongType);
				break;
			case 4:
				printf("ERROR(%d): Array '%s' should be indexed by type int but got %s.\n", errorLine, symbol, rightType);
				break;
			case 5:
				printf("ERROR(%d): Array index is the unindexed array '%s'.\n", errorLine, "UNSURE???");
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


void checkTypes(TreeNode * t, char * name, TreeNode * left, TreeNode * right, bool &leftGood, bool &rightGood, ExpType &wrongLHS, ExpType &wrongRHS, bool &isArrayLHS, bool &isArrayRHS, int &arrayError)
{
	std::string strName(name);

	// for and or booleans
	if (strName == "and" || strName == "or")
	{
		// we don't take arrays
		if(isArrayLHS || isArrayRHS)
		{
			arrayError = 1;
		}
		t->type = boolean;
		if(left->type != boolean)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}
		if(right -> type != boolean)
		{
			rightGood = false;
			wrongRHS = right -> type;
		}
	}
	// for all comparison ops
	if (strName == "<" || strName == ">" || strName == ">=" || strName == "<=")
	{
		// we don't take arrays
		if(isArrayLHS || isArrayRHS)
		{
			arrayError = 1;
		}
		t->type = boolean;
		if(left->type != boolean && left -> type != integer)
		{
			leftGood = false;
			wrongLHS = left -> type;

		}
		if(right -> type != boolean && right -> type != integer)
		{
			rightGood = false;
			wrongRHS = right -> type;
		}
		//Not equal types
		if (right -> type != left -> type)
		{
			leftGood = rightGood = false;
			wrongLHS = left -> type;
			wrongRHS = right -> type;
		}

	}

	if (strName == "")
	{

	}


}

// For unary ops
void checkTypes(TreeNode * t, char * name, TreeNode * right, TreeNode * left, bool &leftGood, ExpType &wrongLHS, ExpType &wrongRHS, bool &isArrayLHS, int &arrayError)
{

}

