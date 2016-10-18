/*************
globals.h
Matthew Daniel
September 20, 2016
Contains the syntax tree node based on the Louden definitis
 *************/

#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "scanType.h"
#include "symbolTable.h"

#define MAXCHILDREN 3


// Global line number
extern int lineno;
extern int indent;
extern int sibCount;
extern int childCount;
extern SymbolTable st;
extern int numErrors;
extern int numWarnings;

enum childSib
{
    non, chi, sib
};

enum NodeKind
{
	DeclK, StmtK, ExpK
};

enum DeclKind
{
	varDeclaration, funDeclaration, recDeclaration, paramDeclaration
};

enum StmtKind
{
	expressionStmt, compoundStmt, selectionStmt, iterationStmt, returnStmt, breakStmt
};

enum ExpKind
{
	OpK, factorK, IdK, constK, AssK, CallK
};

enum ExpType
{
	integer, boolean, character, record, Void, undefined, na, charint, nonvoid
};

// Reflects the struct from the assignment 2 notes
typedef struct treeNode
   { 
	struct treeNode * child[MAXCHILDREN];
	struct treeNode * sibling;
	int lineno;
    NodeKind nodekind;
    union 
    { 
    	DeclKind decl; 
    	StmtKind stmt; 
    	ExpKind exp; 
    } kind;

    union 
    { 
    	TokenData * td;
    	int value;
    	unsigned char cvalue;
    	char * string;
    	char * name;
    	bool bvalue;
    } attr;

    ExpType type;
    bool isArray;
    bool isRecord;
    bool isStatic;
    bool isParam;
    int numChildren;
    char * tokenString;
    bool isFun;

   } TreeNode;

#endif
