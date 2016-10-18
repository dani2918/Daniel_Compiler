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



void checkTypes(TreeNode * t, char * name, TreeNode * left, TreeNode * right, bool &leftGood, bool &rightGood, bool &mismatch, ExpType &wrongLHS, ExpType &wrongRHS, bool &isArrayLHS, bool &isArrayRHS, int &arrayError, ExpType &operandType)
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

		if(left-> type == undefined || right-> type == undefined)
		{
			return;
		}

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
			return;
		}
		// we do take arrays, do we need to make sure they're both arrays?
		// I don't see an error message that would handle that...

		// if(isArrayLHS || isArrayRHS)
		// {
		// 	arrayError = 1;
		// }

		// keep from having cascading errors
		

		if(left->type != boolean && left -> type != integer && left -> type != character)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}
		if(right -> type != boolean && right -> type != integer && left -> type != character)
		{
			rightGood = false;
			wrongRHS = right -> type;
		}
		//Not equal types
		if (right -> type != left -> type)
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
		if(left-> type == undefined || right-> type == undefined)
		{
			return;
		}

		if(left->type != boolean && left -> type != integer && left -> type != character)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}
		if(right -> type != boolean && right -> type != integer && left -> type != character)
		{
			rightGood = false;
			wrongRHS = right -> type;
		}
		//Not equal types
		if (right -> type != left -> type)
		{
			mismatch = true;
			wrongLHS = left -> type;
			wrongRHS = right -> type;
		}
	}

	// for __= types or arithmetic
	if (strName == "+=" || strName == "-=" || strName == "*=" || strName == "/=" || strName == "+" || strName == "-" || strName == "*" || strName == "/" || strName == "/%")
	{
		operandType = integer;
				// we don't take arrays
		if(isArrayLHS || isArrayRHS)
		{
			arrayError = 1;
		}
		t->type = integer;

		if(left-> type == undefined || right-> type == undefined)
		{
			return;
		}

		if(left->type != integer)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}
		if(right -> type != integer)
		{
			rightGood = false;
			wrongRHS = right -> type;
		}

	}

	if (strName == "[")
	{
		operandType = nonvoid;
		if(left-> type == undefined || right-> type == undefined)
		{
			t->type = left->type;
			return;
		}
		// we need an array, if not issue nonarray
		if(!isArrayLHS) // TODO: if is array RHS?
		{
			arrayError = 3;
		}

		
		// we do take arrays, do we need to make sure they're both arrays?
		// I don't see an error message that would handle that...

		// if(isArrayLHS || isArrayRHS)
		// {
		// 	arrayError = 1;
		// }

		// keep from having cascading errors
		

		if(left->type != boolean && left -> type != integer && left -> type != character)
		{
			leftGood = false;
			wrongLHS = left -> type;
		}
		if(right -> type != integer)
		{
			rightGood = false;
			wrongRHS = right -> type;
		}

		if (leftGood && rightGood)
		{
			t-> type = left-> type;
		}
		else
		{
			t -> type = undefined;
		}
	}

	// not gets lumped in with the binary ops for some reason
	


}

// For unary ops
void checkTypes(TreeNode * t, char * name, TreeNode * left, TreeNode * right, bool &leftGood, bool &mismatch, ExpType &wrongLHS, ExpType &wrongRHS, bool &isArrayLHS, int &arrayError, ExpType &operandType)
{
	std::string strName(name);
		//printf("\n\n %s !!\n", strName.c_str());

	// Unary star
	if(strName == "*")
	{
		operandType = integer;
		//printf("\nunary star\n");
		// we need an array, if not issue nonarray
		if(!isArrayLHS) 
		{
			//printf("\narray error 2\n");
			arrayError = 2;
		}

		if(left-> type == undefined)
		{
			t->type = integer;
			return;
		}
		// we do take arrays, do we need to make sure they're both arrays?
		// I don't see an error message that would handle that...

		// if(isArrayLHS || isArrayRHS)
		// {
		// 	arrayError = 1;
		// }

		if(left->type != boolean && left -> type != integer && left -> type != character)
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

}