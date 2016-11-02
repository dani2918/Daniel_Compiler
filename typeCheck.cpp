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



void checkTypes(TreeNode * t, char * name, TreeNode * left, TreeNode * right, bool &leftGood, bool &rightGood, bool &mismatch, ExpType &wrongLHS, ExpType &wrongRHS, bool &isArrayLHS, bool &isArrayRHS, int &arrayError, ExpType &operandType,  bool isFunLHS,  bool isFunRHS)
{
	std::string strName(name);
	
	// for and or booleans
	if (strName == "and" || strName == "or")
	{
		operandType = boolean;
		// we don't take arrays
		if(isArrayLHS || isArrayRHS)
		{
			arrayError = 1;
		}
		t->type = boolean;

		// if(left-> type == undefined || right-> type == undefined)
		// {
		// 	return;
		// }

		if(left->type != boolean && left -> type != undefined)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}
		if(right -> type != boolean && right -> type != undefined)
		{
			rightGood = false;
			wrongRHS = right -> type;
		}
	}
	// for all comparison ops
	if (strName == "<" || strName == ">" || strName == ">=" || strName == "<=")
	{
		operandType = charint;
		// we don't take arrays
		if(isArrayLHS || isArrayRHS)
		{
			arrayError = 1;
		}
		t->type = boolean;

		if(left->type != character && left -> type != integer && left -> type != undefined )
		{
			leftGood = false;
			wrongLHS = left -> type;

		}
		if(right -> type != character && right -> type != integer && right -> type != undefined)
		{
			rightGood = false;
			wrongRHS = right -> type;
		}
		//Not equal types
		if (right -> type != left -> type && right -> type != undefined && left -> type != undefined )
		{
			mismatch = true;
			wrongLHS = left -> type;
			wrongRHS = right -> type;
		}

	}

	// Assign
	if (strName == "=")
	{
		operandType = nonvoid;
		if(left-> type == undefined || right-> type == undefined)
		{
			t->type = left->type;
		}
		// we do take arrays, do we need to make sure they're both arrays?
		// I don't see an error message that would handle that...

		// if(isArrayLHS || isArrayRHS)
		// {
		// 	arrayError = 1;
		// }

		// keep from having cascading errors

		if(left -> type != boolean && left -> type != integer && left -> type != character && left -> type != undefined)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}
		if(right -> type != boolean && right -> type != integer && right -> type != character && right -> type != undefined)
		{
			rightGood = false;
			wrongRHS = right -> type;
		}
		//Not equal types
		if (right -> type != left -> type && left -> type != undefined && right -> type != undefined)
		{
			mismatch = true;
			wrongLHS = left -> type;
			wrongRHS = right -> type;
		}

		if (leftGood)
		{
			t-> type = left-> type;
		}

	}

	// Equality checks
	if (strName == "==" || strName == "!=")
	{
		// we do take arrays, do we need to make sure they're both arrays?
		// I don't see an error message that would handle that...

		// if(isArrayLHS || isArrayRHS)
		// {
		// 	arrayError = 1;
		// }
		operandType = nonvoid;
		t->type = boolean;

		if(left->type != boolean && left -> type != integer && left -> type != character && left -> type != undefined)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}
		if(right -> type != boolean && right -> type != integer && right -> type != character && right -> type != undefined)
		{
			rightGood = false;
			wrongRHS = right -> type;
		}
		//Not equal types
		if (right -> type != left -> type && left -> type != undefined && right -> type != undefined)
		{
			//Try this to fix overkill, print right error
			if(right -> type != Void)
			{
				leftGood = true;
				rightGood = true;
			}
			mismatch = true;
			wrongLHS = left -> type;
			wrongRHS = right -> type;
		}
	}

	// for __= types or arithmetic
	if (strName == "+=" || strName == "-=" || strName == "*=" || strName == "/=" || strName == "+" || strName == "-" || strName == "*" || strName == "/" || strName == "%")
	{
		operandType = integer;
				// we don't take arrays
		if(isArrayLHS || isArrayRHS)
		{
			arrayError = 1;
		}
		t->type = integer;

		if(left->type != integer && left -> type != undefined)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}
		if(right -> type != integer && right -> type != undefined)
		{
			rightGood = false;
			wrongRHS = right -> type;
		}

	}

	if (strName == "[")
	{
		operandType = nonvoid;

		if(left-> type == undefined || right-> type == undefined) //|| left -> kind.exp != IdK)
		{

			t->type = left->type;
			//return;
		}
		// we need an array, if not issue nonarray
		if(!isArrayLHS) // TODO: if is array RHS?
		{
			arrayError = 3;
		}


		// keep from having cascading errors
		if(left->type != boolean && left -> type != integer && left -> type != character && left -> type != undefined)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}
		if(right -> type != integer && right -> type != undefined )
		{
			wrongRHS = right -> type;
			t->isIndexed = false;

			//if there are multiple errors, carry them through
			if(arrayError == 3)
			{
				arrayError = 34;
			}
			else
			{
				arrayError = 4;	
			}

		}
		//If we have an undindex array index
		if (right->isArray && !right->isIndexed && right->kind.exp==IdK)
		{
			//If we have both this error and a non int index
			if(arrayError == 4)
			{
				arrayError = 45;
			}
			//If we have all 3 errors
			else if (arrayError == 34)
			{
				arrayError = 345;
			}
			else if (arrayError == 3)
			{
				arrayError = 35;
			}
			else
			{
				arrayError = 5;
			}
		}

		else
		{
			t->isIndexed = true;
		}

		if (leftGood && rightGood)
		{
			t-> type = left-> type;
		}
		else
		{
			t -> type = undefined;
		}

		if(right->isArray && !right->isIndexed && arrayError == 0)
		{
			printError(85, t->lineno, NULL, 0, na, na, 0);
		}

	}

}

// For unary ops
void checkTypes(TreeNode * t, char * name, TreeNode * left, TreeNode * right, bool &leftGood, bool &mismatch, ExpType &wrongLHS, ExpType &wrongRHS, bool &isArrayLHS, int &arrayError, ExpType &operandType,  bool isFunLHS)
{
	std::string strName(name);
		//printf("\n\n %s !!\n", strName.c_str());

	// Unary star
	if(strName == "*")
	{
		operandType = integer;

		// we need an array, if not issue nonarray
		if(!isArrayLHS && left->type != undefined) 
		{
			//printf("\narray error 2\n");
			arrayError = 2;
		}

		if(left-> type == undefined)
		{
			t->type = integer;
			//return;
		}
		// we do take arrays, do we need to make sure they're both arrays?
		// I don't see an error message that would handle that...

		// if(isArrayLHS || isArrayRHS)
		// {
		// 	arrayError = 1;
		// }


		//The void part may be wrong, but fixes a mismatch with overkill.c-
		if(left->type != boolean && left -> type != integer && left -> type != character && left->type != Void &&left->type != undefined)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}

		if (leftGood)
		{
			t-> type = integer;
		}
		else
		{
			t -> type = undefined;
		}
	}

	if(strName == "?")
	{
		operandType = integer;
		// we don't take arrays
		if(isArrayLHS)
		{
			arrayError = 1;
		}
		t->type = integer;
		if(left->type == undefined)
		{
			return;
		}
		if(left->type != integer)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}	
	}

	if (strName == "++" || strName == "--")
	{
		operandType = integer;
		// we don't take arrays
		if(isArrayLHS)
		{
			arrayError = 1;
		}
		t->type = integer;

		if(left-> type == undefined)
		{
			return;
		}

		if(left->type != integer)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}
	}

	if (strName == "not")
	{
		operandType = boolean;
		// we don't take arrays
		if(isArrayLHS)
		{
			arrayError = 1;
		}
		t->type = boolean;
		

		if(left-> type == undefined)
		{
			return;
		}

		if(left->type != boolean)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}
	}

	if (strName == "-")
	{
		operandType = integer;
				// we don't take arrays
		if(isArrayLHS)
		{
			arrayError = 1;
		}
		t->type = integer;

		if(left->type != integer && left -> type != undefined)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}
	}

}



void checkParams(TreeNode * t, TreeNode * originalDecl, TreeNode * callName, TreeNode * funName)
{
	int paramCount = 1;	
	
	while(1)
	{
		//If both lists are done, then return
		if(t == NULL && originalDecl == NULL)
		{
			return;
		}
		//Too few params passed
		if (t == NULL)
		{
			printError(25, callName->lineno, funName->attr.name, funName->lineno, na, na, 0);
			return;
		}
		//Too many params passed
		if (originalDecl == NULL)
		{
			printError(29, callName->lineno, funName->attr.name, funName->lineno, na, na, 0);
			return;
		}

		//If a parameter type doesn't match (and isn't undefined)
		if(t->type != originalDecl->type && t->type != undefined)
		{
			printError(26, callName->lineno, funName->attr.name, funName->lineno, originalDecl->type, t->type, paramCount);
		}


		//If we wanted an array but didn't get one
		if(!t->isArray && originalDecl->isArray)
		{
			printError(27, callName->lineno, funName->attr.name, funName->lineno, na, na, paramCount);
		}


		//If we got an array but weren't expecting one
		if(t->isArray && !originalDecl->isArray)
		{
			printError(28, callName->lineno, funName->attr.name, funName->lineno, na, na, paramCount);
		}


		t = t->sibling;
		originalDecl = originalDecl -> sibling;

		paramCount++;
	}	
}


