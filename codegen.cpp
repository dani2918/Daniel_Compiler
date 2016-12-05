#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "globals.h"
#include "codegen.h"
#include "emitcode.h"

extern int globalOff;
extern int localOff;

char * tmFileName;

FILE * code;


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
	//code = fopen(tmFileName, "w");
	code = fopen("test.tm", w);
}

void generateCode(TreeNode * t, char * infileName)
{
	createTMFile(infileName);
	emitHeader(infileName);

	fclose(code);
	
}
		
