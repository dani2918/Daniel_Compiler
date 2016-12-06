#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "globals.h"
#include "codegen.h"
#include "emitcode.h"

using namespace std;

extern int globalOff;
extern int localOff;

char * tmFileName;


FILE * code;

#define TEST_MACHINE 0

// 
void createTMFile(char * infileName)
{
	char * lastDot;
	lastDot = strrchr(infileName, '.');
	int cMinusLoc = lastDot - infileName + 1;
	char dst[cMinusLoc];
	tmFileName = (char *)memcpy(dst, infileName, sizeof(dst));
	tmFileName[cMinusLoc] = '\0';
	strcat(tmFileName, "tm");

	//TODO: change this when we're actually testing
	if(TEST_MACHINE)
	{
		code = fopen(tmFileName, "w");
	}
	else
	{
		code = fopen("test.tm", "w");
	}
}

void generateCode(TreeNode * t, char * infileName)
{
	createTMFile(infileName);
	emitHeader(infileName);

	//Also processes tree after IO
	processIO(t);

	processInit(t);

	fclose(code);
	
}
	
void processIO(TreeNode * t)
{
	
	string instructions[] = {"IN", "OUT", "INB", "OUTB", "INC", "OUTC", "OUTNL"};
	string instructionComments[] = {"int", "integer", "bool", "bool", "char", "char", "a newline"};


	for(int i = 0; i < 7; i++)
	{
		t->tmLoc = emitSkip(0) - 1;

        emitComment((char*)"FUNCTION", t->attr.name);

        emitRM((char*)"ST", AC, -1, FP, (char*)"Store return address");

        //Load parameter if it exists (outputs except outnl)
        if(t->child[0] != NULL)
        {
        	emitRM((char*)"LD", AC, -2, FP, (char*)"Load parameter");
        	emitRO((char*)instructions[i].c_str(), AC, 3, 3, (char*)("Output " + instructionComments[i]).c_str());
        	emitRM((char*)"LDC", RT, 0, 6, (char*)"Set return to 0");
        }
        //Else we have an input or outnl
        else
        {
        	//If not outnl
        	if(i != 6)
        	{
        		emitRO((char*)instructions[i].c_str(), RT, 2, 2, (char*)("Grab " + instructionComments[i]).c_str(), (char*)"input ");
        	}
        	else
        	{
        		emitRO((char*)instructions[i].c_str(), AC, 3, 3, (char*)("Output " + instructionComments[i]).c_str());	
        	}
        }
        emitRM((char*)"LD", AC, -1, FP, (char*)"Load return address");
		emitRM((char*)"LD", FP, 0, FP, (char*)"Adjust fp");
    	emitRM((char*)"LDA", PC, 0, AC, (char*)"Return");
		       

        emitComment((char*)"END FUNCTION", t->attr.name);
        emitDivider();
        t = t -> sibling;
	}

	//Move on to rest of code
	processCode(t);

}

void processCodeR(TreeNode * t)
{
	if (t == NULL)
	{
		return;
	}
	processCode(t);
	processCodeR(t->sibling);

}


void processCode(TreeNode * t)
{
	if(t != NULL)
	{
		switch(t->nodekind)
		{
			case DeclK:
				//Switch types of declarations
				switch (t->kind.decl)
				{
					case varDeclaration:

						//Differentiate between var and param

						if(t-> isArray == true)
							{
							}
							else
							{
							}

							// switch types, maybe do this iff -p?
							// if(!capP)
							// {
							// 	switch (t->type)
							// 	{
									
							// 		case integer:
							// 			break;
							// 		case boolean:
							// 			break;
							// 		case character:
							// 			break;	
							// 		case record:
							// 			break;
							// 		default:
							// 			break;
							// 	}
							// }
							// else
							// {
							// }

						break;

					case funDeclaration:
						t ->tmLoc = emitSkip(0) - 1;
						emitComment((char*)"FUNCTION", t->attr.name);

						emitRM((char*)"ST", AC, -1, FP, (char*)"Store return address.");
						for(int i = 0; i < 3; i++) 
				    	{
				    		processCodeR(t->child[i]);
				    	}

			    	 	emitComment((char*)"Add standard closing in case there is no return statement");
						emitRM((char*)"LDC", RT, 0, 6, (char*)"Set return value to 0");	
						emitRM((char*)"LD", AC, -1, FP, (char*)"Load return address");
						emitRM((char*)"LD", FP, 0, FP, (char*)"Adjust fp");
    					emitRM((char*)"LDA", PC, 0, AC, (char*)"Return");



				    	emitComment((char*)"END FUNCTION", t->attr.name);


						// Print return type
						switch (t->type)
							{
								case integer:
									break;
								case boolean:
									break;
								case character:
									break;	
								case Void:
									break;	
								case record:
									break;
								default:
									break;

							}
						break;

					case recDeclaration:
						break;

					case paramDeclaration:
						if(t-> isArray == true)
								{
								}
								else
								{
								}

						// if(!capP)
						// {	
						// 	switch (t->type)
						// 	{
								
						// 		case integer:
						// 			break;
						// 		case boolean:
						// 			break;
						// 		case character:
						// 			break;	
						// 		case record:
						// 			break;
						// 		default:
						// 			break;
						// 	}
						// }
						// else
						// {
						// }

				}
				
				break;
			
			case StmtK:

				//print stmt kind
				switch(t->kind.stmt)
				{
					case compoundStmt:
						emitComment((char*)"COMPOUND");
						emitComment((char*)"Compound Body");
					    for(int i = 0; i < 3; i++) 
				    	{
				    		processCodeR(t->child[i]);
				    	}
				    	emitComment((char*)"END COMPOUND");
						break;
					case returnStmt:
						break;
					case selectionStmt:
						break;
					case iterationStmt:
						break;
					case breakStmt:
						break;
					default:
						break;
				}
				break;

			case ExpK:
				emitComment((char*)"EXPRESSION");
				switch(t->kind.exp)
				{
					case IdK:
						if(t-> isArray == true)
							{
								
							}
							else
							{
							}
						break;

					
					case OpK:
						break;

					case AssK:
						break;

					case constK:
						switch(t -> type)
						{
							case boolean:
								if(t->attr.bvalue == true)
								{
								}
								else
								{
								}
								break;
							case integer:
								break;
							case character:
								break;
							default:
								break;
						}
						break;

					case CallK:
						// Spaces match .tm tests
						emitComment((char*)"                      Begin call to ", t->attr.name);

						//emitRM((char*)"ST", FP, )

						break;

					default:
						break;
				}	

			default:
				break;
			}

	}
}



void processInit(TreeNode * t)
{
	TreeNode * mainDecl;
	mainDecl = (TreeNode *)symTab.lookup("main");
	int mainJump;

	int curLoc = emitSkip(0) - 1;
	emitBackup(0);
	emitRM((char*)"LDA", PC, curLoc, PC, (char*)"Jump to init [backpatch]");
	emitSkip(curLoc);

	emitComment((char*)"INIT");
	emitRM((char*)"LD", GP, 0, 0, (char*)"Set the global pointer");
	emitRM((char*)"LDA", FP, globalOff, GP, (char*)"set first frame at end of globals");
	emitRM((char*)"ST", FP, 0, FP, (char*)"store old fp (point to self)");

	emitComment((char*)"INIT GLOBALS AND STATICS");
	processInitGlobalsStatics(t);
	emitComment((char*)"END INIT GLOBALS AND STATICS");

	emitRM((char*)"LDA", AC, FP, PC, (char*)"Return address in ac");
	mainJump = mainDecl->tmLoc - emitSkip(0);
	emitRM((char*)"LDA", PC, mainJump, PC, (char*)"Jump to main");
	emitRO((char*)"HALT", 0, 0, 0, (char*)"DONE!");

	emitComment((char*)"END INIT");
}

void processInitGlobalsStatics(TreeNode * t)
{

}










