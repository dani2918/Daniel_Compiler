#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include "globals.h"
#include "codegen.h"
#include "emitcode.h"

using namespace std;

extern int globalOff;
extern int localOff;
int fOffset = 0;
int tOffset = 0;
int offset = 0;
int compoundMemSize = 0;
bool storeMode = false;
int curPtr = 0;
char * savedOp = NULL;
int numParams;
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
	processCodeR(t);

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

						for(int i = 0; i < 3; i++) 
			    		{
			    			processCodeR(t->child[i]);
			    		}

						//Differentiate between var and param

						if(t-> isArray == true)
						{
						}
						else
						{
						}
						if(t->isGlobal || t ->isStatic)
						{
							
				    		//emitRM((char*)"ST", AC, t->memLoc, FP, (char*)"Store variable", (char*)t->attr.name);
						}
						else
						{

						}

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
						
				}
				
				break;
			
			case StmtK:

				//print stmt kind
				switch(t->kind.stmt)
				{
					case compoundStmt:
					 	fOffset = compoundMemSize = t->memSize;
						emitComment((char*)"COMPOUND");
						emitComment((char*)"Compound Body");
					    for(int i = 0; i < 3; i++) 
				    	{
				    		processCodeR(t->child[i]);
				    	}
				    	emitComment((char*)"END COMPOUND");
						break;
					case returnStmt:
						emitComment((char*)"RETURN");
						emitRM((char*)"LD", AC, -1, FP,  (char*)"Load return address");
						emitRM((char*)"LD", FP, 0, FP, (char*)"Adjust fp");
    					emitRM((char*)"LDA", PC, 0, AC, (char*)"Return");
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
				TreeNode * left; TreeNode * right;
				left = t->child[0];
				right = t->child[1];
				if(t->isParam)
				{
					numParams++;
					string np = man_to_string(numParams);
					emitComment((char*)"                      Load param", (char*)np.c_str());

					//TODO: Check this
					//fOffset -= 2;
				}
				// else
				// {
				// 	
				// }
				switch(t->kind.exp)
				{
				

					case IdK:

						if(t->isStatic || t->isGlobal) 
						{
							curPtr = GP;
						}
	       				else
	       				{ 
	       					curPtr = FP;
	       				}

	   					if(!storeMode)
						{
							if(t-> isArray == true)
							{
								if(t->child[0] != NULL)
								{
									processCodeR(t->child[0]);
									emitRM((char*)"LDA", 5, t->memLoc, curPtr, (char*)"Load address of base of array", (char*)t->attr.name);
									
								}
								else
								{
									emitRM((char*)"LDA", 5, t->memLoc, curPtr, (char*)"Load address of base of array", (char*)t->attr.name);
								}
							}
							else
							{
								emitRM((char*)"LD", AC, t->memLoc, curPtr, (char*)"Load variable", (char*)t->attr.name);
							}
						}
						else
						{
							if(t->isArray)
							{	
								// Restore index at offset
								emitRM((char*)"LD", AC1, (fOffset + tOffset), FP, (char*)"Restore index");
								emitRM((char*)"LDA", AC2, t->memLoc, curPtr, (char*)"Load address of base of array", (char*)t->attr.name);
								emitRO((char*)"SUB", AC2, AC2, AC1, (char*)"Compute offset of value");


								emitRM((char*)"ST", AC, 0, AC2, (char*)"Store variable", (char*)t->attr.name);

							}
							else
							{
								//If we're in an assignment, store
								if(savedOp != NULL && storeMode)
								{
									emitRM((char*)"ST", AC, t->memLoc, curPtr, (char*)"Store variable", (char*)t->attr.name);
									storeMode = false;
								}
								
							}
						}
						break;

					
					case OpK:
						if(t->isStatic || t->isGlobal) 
						{
							curPtr = GP;
						}
           				else
           				{ 
           					curPtr = FP;
           				}
           				savedOp = t->attr.name;

						//processCodeR(t->child[0]);
						if(t->isUnary)
						{
							processCodeR(t->child[0]);
							if (strcmp(savedOp, "*") == 0)
							{
								emitRM((char*)"LD", AC, 1, AC, (char*)"Load array size");
							}	
							else if (strcmp(savedOp, "?") == 0)
							{
								emitRO((char*)"RND", AC, AC, 6, (char*)"Op", savedOp);
							}
							else if (strcmp(savedOp, "not") == 0)
							{
								emitRM((char*)"LDC", AC1, 1, AC3, (char*)"Load 1");
								emitRO((char*)"XOR", AC, AC, AC1, (char*)"Op NOT");
							}
						}
						else
						{

							processCodeR(t->child[0]);
							if(strcmp(savedOp, "[") != 0)
							{
								int copytOffset = tOffset;
								tOffset --;
								emitRM((char*)"ST", AC, fOffset + copytOffset, FP, (char*)"Save left side");
								processCodeR(t->child[1]);
								emitRM((char*)"LD", AC1, fOffset + copytOffset, FP, (char*)"Load left into ac1");
							}
						}

						//annoyingly can't do a switch stmt on a char *

						if (strcmp(savedOp, "*") == 0)
						{
							emitRO((char*)"MUL", AC, AC1, AC, (char*)"Op", savedOp);
						}	
						else if (strcmp(savedOp, "+") == 0)
						{
							emitRO((char*)"ADD", AC, AC1, AC, (char*)"Op", savedOp);
						}
						else if (strcmp(savedOp, "-") == 0)
						{
							emitRO((char*)"SUB", AC, AC1, AC, (char*)"Op", savedOp);
						}
						else if (strcmp(savedOp, "/") == 0)
						{
							emitRO((char*)"DIV", AC, AC1, AC, (char*)"Op", savedOp);
						}
						else if (strcmp(savedOp, ">") == 0)
						{
							emitRO((char*)"TGT", AC, AC1, AC, (char*)"Op", savedOp);
						}
						else if (strcmp(savedOp, "<") == 0)
						{
							emitRO((char*)"TLT", AC, AC1, AC, (char*)"Op", savedOp);
						}
						else if (strcmp(savedOp, ">=") == 0)
						{
							emitRO((char*)"TGE", AC, AC1, AC, (char*)"Op", savedOp);
						}
						else if (strcmp(savedOp, "<=") == 0)
						{
							emitRO((char*)"TLE", AC, AC1, AC, (char*)"Op", savedOp);
						}
						else if (strcmp(savedOp, "!=") == 0)
						{
							emitRO((char*)"TNE", AC, AC1, AC, (char*)"Op", savedOp);
						}
						else if (strcmp(savedOp, "==") == 0)
						{
							emitRO((char*)"TEQ", AC, AC1, AC, (char*)"Op", savedOp);
						}
						else if (strcmp(savedOp, "and") == 0)
						{
							emitRO((char*)"AND", AC, AC1, AC, (char*)"Op AND");
						}
						else if (strcmp(savedOp, "or") == 0)
						{
							emitRO((char*)"OR", AC, AC1, AC, (char*)"Op OR");
						}
						else if (strcmp(savedOp, "%") == 0)
						{
							emitRO((char*)"DIV", AC2, AC1, AC, (char*)"Op", savedOp);
							emitRO((char*)"MUL", AC2, AC2, AC, (char*)"");
							emitRO((char*)"SUB", AC, AC1, AC2, (char*)"");
						}

						break;

					case AssK:

						emitComment((char*)"EXPRESSION");
						savedOp = t->attr.name;
						storeMode = true;

						if(left->child[0] != NULL)
						{
							if(left->child[0]->isArray)
							{
								processCodeR(left->child[1]);
								
								emitRM((char*)"ST", AC, fOffset + tOffset, FP, (char*)"Save index");
								//tOffset--;

							}
						}

						
						//If binary, process RHS first
						if(!t->isUnary)
						{
							processCodeR(t->child[1]);
						}
						processCodeR(t->child[0]);

						

						savedOp = NULL;
						//tOffset --;

						break;

					case constK:
						switch(t -> type)
						{
							case boolean:
								emitRM((char*)"LDC", AC, t->attr.bvalue, AC3, (char*)"Load Boolean constant");
								if(t->attr.bvalue == true)
								{
								}
								else
								{
								}
								break;
							case integer:
								emitRM((char*)"LDC", AC, t->attr.value, AC3, (char*)"Load integer constant");
								break;
							case character:
								emitRM((char*)"LDC", AC, t->attr.cvalue, AC3, (char*)"Load character constant");
								break;
							default:
								break;
						}
						break;

					case CallK:
						TreeNode * callName;
						callName = (TreeNode*)symTab.lookup(t->attr.name);
						
						//'save' all variables so that we don't lose 
						// values in recruisve call
						fOffset = compoundMemSize;
						int funJump;
						int copyfOffset; copyfOffset = fOffset; 
						int copytOffset; copytOffset = tOffset;

						// This changes the offset for params in recursive call
						// But not for anything in CallK
						fOffset -= 2;

						// int copyCompSize; copyCompSize = compoundMemSize;
						numParams = 0;
						offset = copytOffset + copyfOffset;

						emitComment((char*)"EXPRESSION");
						// Spaces match .tm tests
						emitComment((char*)"                      Begin call to ", t->attr.name);
						emitRM((char*)"ST", FP, offset, FP, (char*)"Store old fp in ghost frame");


						for(int i = 0; i < 3; i++) 
						{
							processCodeR(t->child[i]);
						}

						//restore after recursion
						fOffset = copyfOffset;
						tOffset = copytOffset;
						//compoundMemSize = copyCompSize;

						
						emitComment((char*)"                      Jump to", t->attr.name);
						emitRM((char*)"LDA", FP, offset, FP, (char*)"Load address of new frame");
						emitRM((char*)"LDA", AC, FP, PC, (char*)"Return address in ac");

						funJump = callName->tmLoc - emitSkip(0);
						emitRM((char*)"LDA", PC, funJump, PC, (char*)"CALL", t->attr.name);
						emitRM((char*)"LDA", AC, 0, RT, (char*)"Save the result in ac");
						emitComment((char*)"                      End call to", t->attr.name);

						// Resets fOff (see above)
						fOffset += 2;
						break;

					default:
						break;
					left = right = NULL;
				}	

			default:
				break;
			}
		if(t->isParam)
		{
			emitRM((char*)"ST", AC, fOffset, FP, (char*)"Store parameter");
			fOffset --;
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

//Function to replace to_string 
//Since we can't compile w c++ 11 on test machine
std::string man_to_string(int i)
{
	stringstream ss;
    ss << i;
    return ss.str();
}








