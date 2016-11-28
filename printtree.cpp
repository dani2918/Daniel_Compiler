/* 	Matthew Daniel
	printtree.cpp

*/ 


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "globals.h"
#include "syntaxTree.h"
#include "printtree.h"

int sibCount;
int childCount;
int indent;
bool capP = false;
extern SymbolTable symTab;



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

void printTree(TreeNode * t, bool cp)
{
	sibCount = 0;
	childCount = 0;
	indent = 0;

	if (cp)
	{
		capP = true;
	}

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

								// switch types, maybe do this iff -p?
								if(!capP)
								{
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
								else
								{
									printf("%s", arrMsgToggle );
								}

							break;

						case funDeclaration:
							printf("Func %s ", t->attr.name);

							// Print return type
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
									default:
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

							if(!capP)
							{	
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
							else
							{
								printf("%s", arrMsgToggle );
							}

					}
					
					break;
				
				case StmtK:

					//print stmt kind
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
									printf("%s", arrMsgToggle );
								}
								else
								{
									arrMsgToggle = "";
								}
							break;

						
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

			if (capP)
			{
				bool printSize = false;
				// Print reference, size, location with -P option
				switch (t->nodekind)
				{
					case DeclK:
						
						switch(t->kind.decl)
						{
							case funDeclaration:
								printf("[" );
								if(t->isGlobal)
								{
									printf("ref: Global, ");
								}
								else
								{
									printf("ref: Local, ");
								}
								printSize = true;
								break;
							case paramDeclaration:
								printf(" [" );
								printf("ref: Param, ");
								printSize = true;
								break;
							case varDeclaration:
								printSize = true;
								printf(" [" );
								if(t->isGlobal)
								{
									printf("ref: Global, ");
								}
								else if (t->isStatic)
								{
									printf("ref: Static, ");
								}
								else
								{
									printf("ref: Local, ");
								}
								break;
							default:
								printSize = false;
								break;
						}
						break;

					case ExpK:
						if (t->kind.exp == IdK)
						{
							printf(" [" );
							printSize = true;

							//Determine if we're in local or global scope
							if(t->type == undefined && !t->badCall)
							{
								//printf("symtab depth is: %d\n", symTab.depth());
								printf("ref: None, ");
							}
							else if (t->isParam)
							{
								//printf("symtab depth is: %d\n", symTab.depth());
								printf("ref: Param, ");
							}
							//Treat like a global if we treated func like variable
							else if (t->isGlobal)
							{
								printf("ref: Global, ");
							}
							else if (t->isStatic)
							{
								printf("ref: Static, ");
							}
							else
							{
								printf("ref: Local, ");
							}
						}

						if(t->kind.exp == CallK)
						{
							printSize = true;
							printf("[ref: None, ");
						}

					default:
						break;	
					
				}
				if(printSize)
				{
					printf("size: %d, loc: %d] ", t->memSize, t->memLoc);
				}


				switch (t -> type)
				{
					case Void:
						printf("[type void] ");
						break;
					case integer:
						printf("[type int] ");
						break;
					case boolean:
						printf("[type bool] ");
						break;
					case character:
						printf("[type char] ");
						break;
					case record:
						printf("[type record] ");
						break;
					case undefined:
						printf("[undefined type] ");
						break;
					default:	
						printf("[type void] ");
						break;
				}
			}
			//print line number stored from scantype at time of making new node
			printf("[line: %d]\n", t->lineno );
			
		}
	
}