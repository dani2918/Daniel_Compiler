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

#define MAXCHILDREN 3

// enum TokenType
// {
// 	NUMCONST, CHARCONST, ID, BOOLCONST,
// 	NOT, AND, OR, RECORD, STATIC, INT, BOOL, CHAR, IF, ELSE, WHILE, RETURN, BREAK,
//  	RAND, DOT,
// 	ADDASS, SUBASS, MULASS, DIVASS, DEC, INC,
// 	EQ, NOTEQ, LESSEQ, LT, GRTEQ, GT,
// 	ASS, MUL, ADD, SUB, DIV, MOD,
// 	LPAREN, RPAREN, LBRAC, RBRAC, LCUR, RCUR, COMMA, COL, SEMI
// };



// Global line number
extern int lineno;
extern int indent;
extern int sibCount;
extern int childCount;

enum NodeKind
{
	DeclK, StmtK, ExpK
};

enum DeclKind
{
	varDeclaration, funDeclaration, recDeclaration
};

enum StmtKind
{
	expressionStmt, compoundStmt, selectionStmt, iterationStmt, returnStmt, breakStmt
};

enum ExpKind
{
	simpleExpression
};

enum ExpType
{
	integer, boolean, character
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
    	TokenData td;
    	int value;
    	unsigned char cvalue;
    	char * string;
    	char * name;
    } attr;

    ExpType type;
    bool isArray;
    bool isRecord;
    bool isStatic;
    bool isParam;

   } TreeNode;

#endif