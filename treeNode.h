/*************
treeNode.h
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

typedef struct treeNode
{
	struct treeNode * child[MAXCHILDREN];
	struct treeNode * sibling;
	int lineno;

} TreeNode;

#endif
