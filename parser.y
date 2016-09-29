//TEST
%{
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include "globals.h"
 #include "scanType.h"
 #include "syntaxTree.h"


 #include "parser.tab.h"



 extern int yylex();
 extern int yyparse();
 extern FILE *yyin;
 extern int lineno;

 //Like the TreeNode from tiny.y
 static TreeNode * savedTree;
 int savedLineNo;

 ExpType storedType;
 bool isStatic = false;
 TreeNode * nullablePlaceholder;

// To track epsilon productions
 int firstTimeThrough = 0;

//#define YYERROR_VERBOSE 1
void yyerror(const char *errMsg)
{
 	printf("ERROR(%d): %s\n", lineno, errMsg);
}

void printToken(int lineno, char* tokenString)
{
	printf("Line %d Token: %s\n", lineno, tokenString);
}

void printErrToken(int lineno, char* tokenString)
{
	printf("ERROR(%d): Invalid or misplaced input character: \"%s\"\n", lineno, tokenString);
}

 %}


%token <tokenData> NUMCONST
%token <tokenData> CHARCONST
%token <tokenData> ID
%token <tokenData> BOOLCONST
%token <tokenData> NOT AND OR RECORD STATIC INT BOOL CHAR IF ELSE WHILE RETURN BREAK
%token <tokenData> RAND DOT
%token <tokenData> ADDASS SUBASS MULASS DIVASS DEC INC
%token <tokenData> EQ NOTEQ LESSEQ LT GRTEQ GT
%token <tokenData> ASS MUL ADD SUB DIV MOD
%token <tokenData> LPAREN RPAREN LBRAC RBRAC LCUR RCUR COMMA COL SEMI
%token <tokenData> ERR
%error-verbose





%union
{
	TokenData *tokenData;
}

%union
{
	TreeNode *treeNode;
}

%union
{
	ExpType expType;
	int number; 
	TokenData * td;
	TreeNode * t;
	char * name;

}

%union
{
	char * c;
}


%type <treeNode> declarationList declaration
%type <treeNode> varDeclaration funDeclaration recDeclaration varDeclList varDeclInitialize varDeclId simpleExpression
	%type <treeNode> params paramList paramTypeList paramIdList paramId
%type <treeNode> statement otherStatement selectIterStmt expressionStmt compoundStmt returnStmt breakStmt
	%type <treeNode> localDeclarations scopedVarDeclaration statementList
%type <treeNode> expression firstmatched matched unmatched
	%type <treeNode> andExpression unaryRelExpression relExpression sumExpression term unaryExpression
	%type <treeNode> factor immutable mutable
	%type <treeNode> argList args call constant
%type <expType> returnTypeSpecifier typeSpecifier scopedTypeSpecifier
%type <td> relop sumop mulop unaryop




%%
program					: declarationList
							{savedTree = $1;}
						;

declarationList			: declarationList declaration 
							{
								TreeNode * t = $1;
								if (t != NULL)
								{
									//printf("t is NULL\n");
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $2;
									$$ = $1;
								}
								else 
								{
									//printf("t is not NULL\n");
									$$ = $2;
								}
							}

						| declaration 
							{ $$ = $1;}
						;


declaration 			: varDeclaration
							{$$ = $1; }	
						| funDeclaration 
							{$$ = $1; }
						| recDeclaration 
							{$$ = $1; }
						;

// TODO: RECORD
recDeclaration 			: RECORD ID LCUR localDeclarations RCUR
						//	{
						//		$$ = newRecNode()
						//	}
						;

varDeclaration			: typeSpecifier varDeclList SEMI 
							{
								storedType = $1; 
								$$ = $2;
 							}
						;

// TOOD: scopedVarDeclaration
scopedVarDeclaration 	: scopedTypeSpecifier varDeclList SEMI
							{
								storedType = $1;
								$$ = $2;
							}
						;

varDeclList				: varDeclList COMMA varDeclInitialize
							{
								TreeNode * t = $1;
								if (t != NULL)
								{
									//printf("t is not NULL\n");
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $3;
									
								}
								else 
								{
									//printf("t is NULL\n");
									t->sibling = $3;
									
								}
								$$ = $1;
								
							}							


								 

						| varDeclInitialize
							{ 
								$$ = $1; 
							}
						;

varDeclInitialize 		: varDeclId
							{	
 								$$ = $1;
							}
						| varDeclId COL simpleExpression
							{
								$$ -> child[0] = $3;
								$$ = $1;
							}
						;


varDeclId				: ID 
							{
								$$ = newExpNode(IdK);
								$$ -> attr.name = strdup($1 -> tokenString);
								$$->type = storedType; 
								$$->isArray = false;
								$$ -> isStatic = isStatic;
							}
						| ID LBRAC NUMCONST RBRAC
							{
								$$ = newExpNode(IdK);
								$$ -> attr.name = strdup($1 -> tokenString);
								$$->type = storedType; 
								$$->isArray = true; //printf("Array\n");
								$$ -> isStatic = isStatic;
							}		
						;


scopedTypeSpecifier 	: STATIC typeSpecifier
							{
								isStatic = true; 
								$$ = $2;
							}
						| typeSpecifier
							{ $$ = $1;}
						;

typeSpecifier 			: returnTypeSpecifier 
							{
								$$ = $1;
							}

							//TODO: RECORD part
						| RECORD /*MAYBE rectype?*/
//							{
//								$$ = $1;
//							}
						;

returnTypeSpecifier		: INT 
							{
								storedType = integer;
							}
						| BOOL
							{
								storedType = boolean; 
							}
						| CHAR
							{
								storedType = character;
							}
						;

funDeclaration			: typeSpecifier ID LPAREN params RPAREN statement
							{
								printf("we have this one\n");
								storedType = $1;
								$$ = newDeclNode(funDeclaration);
								$$ -> lineno = $2 -> lineno;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> type = storedType; printf("storedType is: %d\n", storedType);
								$$ -> child[0] = $4;
								$$ -> child[1] = $6; //printf("line 255\n"); printf("lineno: %d\n", $$->child[1]->lineno);
							}

						| ID LPAREN params RPAREN statement
							{
								$$ = newDeclNode(funDeclaration);
								$$ -> lineno = $2 -> lineno;
								$$ -> attr.name = strdup($1 -> tokenString);
								$$ -> child[0] = $3;
								$$ -> child[1] = $5; 
							}
						;

params					: paramList
							{
								$$ = $1;
							}
						| /* empty */
							{
								$$ = NULL;
							}
						;

paramList				: paramList SEMI paramTypeList 
							{
								TreeNode * t = $1;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $3;
									
								}
								else 
								{
									t->sibling = $3;
									
								}
								$$ = $1;
							}

						| paramTypeList
							{ 
								$$ = $1; 
							}
						;


paramTypeList			: typeSpecifier paramIdList
							{
								storedType = $1;
								$$ = $2;
							}
						;

paramIdList				: paramIdList COMMA paramId 
							{
								TreeNode * t = $1;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $3;
									
								}
								else 
								{
									t->sibling = $3; 
									
								}
								$$ = $1;
							}
							

						| paramId
							{ 
								$$ = $1; 
							}
						;

paramId 				: ID 
							{
								$$ = newDeclNode(varDeclaration); 
								$$ -> attr.name = strdup($1 -> tokenString);
								$$->type = storedType; 
								$$->isArray = false;
								$$->isParam = true;
							}
						| ID LBRAC RBRAC
							{
								$$ = newDeclNode(varDeclaration);
								$$ -> attr.name = strdup($1 -> tokenString);
								$$->type = storedType; 
								$$->isArray = true;
								$$->isParam = true;
							}		
						;


statement 				: selectIterStmt
							{$$ = $1;}
						| otherStatement
							{
								$$ = $1; //printf("line 360\n");
							}
						;

otherStatement 			: expressionStmt 
							{$$ = $1;}
						| compoundStmt
							{$$ = $1;}
						| returnStmt
							{$$ = $1;}
						| breakStmt
							{$$ = $1;}
						;
					

compoundStmt			: LCUR localDeclarations statementList RCUR
							{
								$$ = newStmtNode(compoundStmt); //printf("compoundStmt!\n\n");
								$$ -> lineno = $1 -> lineno;
								$$ -> child[0] = $2;
								$$ -> child[1] = $3; //printf("Line 385\n");
							}
						;

localDeclarations		: localDeclarations scopedVarDeclaration
							{
								if (firstTimeThrough == 1)
								{
									$$  = $2;
									firstTimeThrough = 0;
								}
								else
								{
									$$ = $1;
								}
								
							}
							
						| /* empty */
							{
								//$$ = newStmtNode(expressionStmt);
								firstTimeThrough = 1;
								//$$ = NULL;
							}
						;

statementList			: statementList statement
							{
								if (firstTimeThrough == 1)
								{
									$$  = $2;
									firstTimeThrough = 0;
								}
								else
								{
									$$ = $1;
								}
							
							}

						| /* empty */
							{
								//printf("got here!\n\n\n");
							//	$$ = newStmtNode(expressionStmt);
								firstTimeThrough = 1;
								//$$ = NULL;
							}
						;

expressionStmt			: expression SEMI 
							{
								//$$ = newStmtNode(expressionStmt);
								$$ = $1;
							}

						| SEMI
						;



selectIterStmt 			: firstmatched 
							{ $$ = $1;} 
						| unmatched
							{ $$ = $1;} 
						; 

firstmatched			: IF LPAREN simpleExpression RPAREN matched ELSE matched 
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> child[0] = $3; 
								$$ -> child[1] = $5;
								$$ -> child[2] = $7;
							}
						| WHILE LPAREN simpleExpression RPAREN matched
							{
								$$ = newStmtNode(iterationStmt);
								$$ -> child[0] = $3;
								$$ -> child[1] = $5;
							}
						;

matched					: IF LPAREN simpleExpression RPAREN matched ELSE matched 
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> child[0] = $3; 
								$$ -> child[1] = $5;
								$$ -> child[2] = $7;
							}
						| WHILE LPAREN simpleExpression RPAREN matched
							{
								$$ = newStmtNode(iterationStmt);
								$$ -> child[0] = $3; 
								$$ -> child[1] = $5;
							}
						| otherStatement
							{
								$$ = $1;
							}
						;

unmatched				: IF LPAREN simpleExpression RPAREN matched	
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> child[0] = $3;
								$$ -> child[1] = $5;
							}
						| IF LPAREN simpleExpression RPAREN unmatched	
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> child[0] = $3;
								$$ -> child[1] = $5;
							}					
						| IF LPAREN simpleExpression RPAREN ELSE unmatched
							{
								$$ = newStmtNode(selectionStmt);
								$$ -> child[0] = $3;
								$$ -> child[1] = $6;
							}
						| WHILE LPAREN simpleExpression RPAREN unmatched	
							{
								$$ = newStmtNode(iterationStmt);
								$$ -> child[0] = $3;
								$$ -> child[1] = $5;
							}					
						| WHILE LPAREN simpleExpression RPAREN ELSE unmatched
							{
								$$ = newStmtNode(iterationStmt);
								$$ -> child[0] = $3;
								$$ -> child[1] = $6;
							}		
						;


returnStmt				: RETURN SEMI
							{
								$$ = newStmtNode(returnStmt); // printf("line 521\n");

							}
						| RETURN expression SEMI
							{
								$$ = newStmtNode(returnStmt);
								$$ -> child[0] = $2;
							}
						;

breakStmt 				: BREAK SEMI
							{
								$$ = newStmtNode(breakStmt);
							}
						;
//_________________________________________________________________________________


expression 				: mutable ASS expression 
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> attr.td = $2;
							}
						| mutable ADDASS expression
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> attr.td = $2;
							}
						| mutable SUBASS expression
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> attr.td = $2;
							}
						| mutable MULASS expression
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> attr.td = $2;
							}
						| mutable DIVASS expression
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> attr.td = $2;
							}
						| mutable INC expression
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> attr.td = $2;
							}
						| mutable DEC expression
							{
								$$ = newExpNode(OpK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> attr.td = $2;
							}
						| simpleExpression 
							{
								$$ = $1;
							}
						;


simpleExpression		: simpleExpression OR andExpression
							{
								$$ = newExpNode(factorK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> attr.td = $2;
							}
						| andExpression
							{
								$$ = $1;
							}
						;

	
andExpression			: andExpression AND unaryRelExpression
						{
								$$ = newExpNode(factorK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> attr.td = $2;
						}
						| unaryRelExpression
							{
								$$ = $1;
							}
						;

unaryRelExpression		: NOT unaryRelExpression
							{
								$$ = $2;
							}
						| relExpression
							{
								$$ = $1;
							}
						;

relExpression			: sumExpression relop sumExpression
							{
								$$ = newExpNode(factorK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> attr.td = $2;
							}

						| sumExpression
							{
								$$ = $1;
							}
						;	


relop 					: LESSEQ 
							{$$ = $1;}
						| LT
							{$$ = $1;}
						| GT
							{$$ = $1;}
						| GRTEQ
							{$$ = $1;}
						| EQ
							{$$ = $1;}
						| NOTEQ
							{$$ = $1;}
						;

sumExpression			: sumExpression sumop term
							{
								$$ = newExpNode(factorK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> attr.td = $2;
							}
						| term
							{
								$$ = $1;
							}
						;

sumop 					: ADD
							{$$ = $1;}
						| SUB
							{$$ = $1;}
						;

term					: term mulop unaryExpression
							{
								$$ = newExpNode(factorK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
								$$ -> attr.td = $2;
							}
						| unaryExpression
							{$$ = $1;}
						;

mulop					: MUL
							{$$ = $1;}
						| DIV
							{$$ = $1;}
						| MOD
							{$$ = $1;}
						;						

unaryExpression			: unaryop unaryExpression
							{
								$$ = newExpNode(factorK);
								$$ -> child[0] = $2;
								$$ -> attr.td = $1;
							}
						| factor
							{$$ = $1;}
						;

unaryop 				: SUB
							{$$ = $1;}
						| MUL
							{$$ = $1;}
						| RAND
							{$$ = $1;}
						;

factor					: immutable 
							{$$ = $1;}
						| mutable
							{$$ = $1;}
						;

mutable					: ID 
							{
								$$ = newExpNode(IdK);
								$$ -> attr.name = strdup($1 -> tokenString);
							//	$$->type = storedType; 
								$$->isArray = false;
							}
						| mutable LBRAC expression RBRAC 
							{
								$$ = newExpNode(IdK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
							}
						| mutable DOT ID
							{
								$$ = newExpNode(IdK);
								$$ -> child[0] = $1;
								
								TreeNode * t;
								t = newExpNode(IdK);
								t -> attr.name = strdup($3 -> tokenString);
								//$$->type = storedType; 
								t ->isArray = false;
								$$ -> child[1] = t;
							}
						;						

immutable				: LPAREN expression RPAREN
							{	// MAY BE WRONG
								$$ = $2;
							} 
						| call
							{
								$$ = $1;
							}
						| constant 
							{
								$$ = $1;
							}
						; 

call					: ID LPAREN args RPAREN 
							{
								$$ = newExpNode(IdK);
								$$ -> child[0] = $3;

								$$ -> attr.name = strdup($1 -> tokenString);
								//$$->type = storedType; 
								$$ ->isArray = false;

							}
						;

args 					: argList	
							{
								$$ = $1;
							}
						| /* empty */
							{
								$$ = NULL;
							}
						;


argList					: argList COMMA expression 
							{
								$$ = newExpNode(constK);
								$$ -> child[0] = $1;
								$$ -> child[1] = $3;
							}

						| expression
							{
								$$ = $1;
							}
						;

constant	 			: NUMCONST 
							{
								$$ = newExpNode(constK);
								$$ ->attr.value = $1->numVal;
							}	
						| CHARCONST 
							{
								$$ = newExpNode(constK);
								$$ ->attr.cvalue = $1->charVal;
							}	
						| BOOLCONST 
							{
								$$ = newExpNode(constK);
								$$ -> attr.bvalue = $1->bvalue;
							}
						;

%%

int main(int argc, char *argv[])
{

	extern int yydebug;
	int optCount = 1;

	// for options
	int opt; 

	while ((opt = getopt(argc, argv, "d::")) != -1)
	{
		switch (opt)
		{
			case 'd':
				yydebug = 1;
				break;
		}
		optCount++;
	}
	FILE *infile = fopen(argv[optCount], "r");
	yyin = infile;
	yyparse();
	fclose(yyin);

	printTree(savedTree);

	return 0;
}
