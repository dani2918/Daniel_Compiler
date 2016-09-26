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

#define MAXCHILDREN 5

// Global line number
extern int lineno;

typedef struct treeNode
   { 
   	struct treeNode * child[MAXCHILDREN];
    struct treeNode * sibling;
  	int lineno;
   // NodeKind nodekind;
    // union { StmtKind stmt; ExpKind exp;} kind;
    // union 
    // 	{ 
    // 		TokenType op;
    //         int val;
    //         char * name; 
    //     } attr;
     //ExpType type; /* for type checking of exps */
   } TreeNode;

#endif
