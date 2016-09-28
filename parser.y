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
	TokenData td;
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
	%type <treeNode> mutable andExpression unaryRelExpression relExpression sumExpression term unaryExpression
	%type <treeNode> factor 
	%type <treeNode> argList args 
%type <expType> returnTypeSpecifier typeSpecifier 




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
								$$ = $2;
 							}
						;

// TOOD: scopedVarDeclaration
scopedVarDeclaration 	: scopedTypeSpecifier varDeclList SEMI
							{
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
								$$ = newDeclNode(varDeclaration);
								$$ -> attr.name = strdup($1 -> tokenString);
								$$->type = storedType; 
								$$->isArray = false;
							}
						| ID LBRAC NUMCONST RBRAC
							{
								$$ = newDeclNode(varDeclaration);
								$$ -> attr.name = strdup($1 -> tokenString);
								$$->type = storedType; 
								$$->isArray = true;
							}		
						;

//TODO: scopedTypeSpecifier
scopedTypeSpecifier 	: STATIC typeSpecifier
						| typeSpecifier
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
								$$ = newDeclNode(funDeclaration);
								$$ -> lineno = $2 -> lineno;
								$$ -> attr.name = strdup($2 -> tokenString);
								$$ -> type = storedType;
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
								$$ -> child[1] = $3;
							}
						;

localDeclarations		: localDeclarations scopedVarDeclaration
							{
								TreeNode * t = $1;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $2;
									
								}
								else 
								{
									$$ = newDeclNode(varDeclaration);
									$$->sibling = $2; 
									
								}
								$$ = $1;
							}
							
						| /* empty */
							{
								$$ = NULL;
							}
						;

statementList			: statementList statement
							{
								TreeNode * t = $1; //printf("got here\n");
								if (t != NULL)
								{	
									//printf("t not null\n");
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $2;									
								}
								else 
								{
									$$ = newStmtNode(expressionStmt);
									//printf("t  null\n");
									$$->sibling = $2; 
									//printf("t  null\n");//LOOK FOR FIX HERE!
								}
								$$ = $1;
							}

						| /* empty */
							{
								$$ = NULL;
							}
						;

expressionStmt			: expression SEMI 
							{
								$$ = newStmtNode(expressionStmt);
								$$ = $1;
							}
						| SEMI
						;


/* TODO: Fix if/while*/

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
								$$ = newStmtNode(returnStmt);// printf("line 521\n");
							}
						| RETURN expression SEMI
							{
								$$ = newStmtNode(returnStmt);
								$$ -> child[0] = $2
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
								TreeNode * t = $3;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $1;
									
								}
								else 
								{
									t->sibling = $1; 
									
								}
								$$ = $3;
							}
						| mutable ADDASS expression
							{
								TreeNode * t = $3;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $1;
									
								}
								else 
								{
									t->sibling = $1; 
									
								}
								$$ = $3;
							}
						| mutable SUBASS expression
							{
								TreeNode * t = $3;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $1;
									
								}
								else 
								{
									t->sibling = $1; 
									
								}
								$$ = $3;
							}
						| mutable MULASS expression
							{
								TreeNode * t = $3;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $1;
									
								}
								else 
								{
									t->sibling = $1; 
									
								}
								$$ = $3;
							}
						| mutable DIVASS expression
							{
								TreeNode * t = $3;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $1;
									
								}
								else 
								{
									t->sibling = $1; 
									
								}
								$$ = $3;
							}
						| mutable INC expression
							{
								TreeNode * t = $3;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $1;
									
								}
								else 
								{
									t->sibling = $1; 
									
								}
								$$ = $3;
							}
						| mutable DEC expression
							{
								TreeNode * t = $3;
								if (t != NULL)
								{
									while (t->sibling != NULL)
									{
										t = t-> sibling;
									}
									t->sibling = $1;
								}
								else 
								{
									t->sibling = $1; 
									
								}
								$$ = $3;
							}
						| simpleExpression 
							{
								$$ = $1;
							}
						;


simpleExpression		: simpleExpression OR andExpression
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
						| andExpression
							{
								$$ = $1;
							}
						;

	
andExpression			: andExpression AND unaryRelExpression
						{
							TreeNode * t = $1; //printf("got here\n");
							if (t != NULL)
							{	
								//printf("t not null\n");
								while (t->sibling != NULL)
								{
									t = t-> sibling;
								}
								t->sibling = $3;									
							}
							else 
							{
								$$ = newStmtNode(expressionStmt);
								//printf("t  null\n");
								$$->sibling = $3; 
								//printf("t  null\n");//LOOK FOR FIX HERE!
							}
							$$ = $1;
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

						| sumExpression
							{
								$$ = $1;
							}
						;	


relop 					: LESSEQ 
						| LT
						| GT
						| GRTEQ
						| EQ
						| NOTEQ
						;

sumExpression			: sumExpression sumop term
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
						| term
							{
								$$ = $1;
							}
						;

sumop 					: ADD
						| SUB
						;

term					: term mulop unaryExpression
						| unaryExpression
						;

mulop					: MUL
						| DIV
						| MOD
						;						

unaryExpression			: unaryop unaryExpression
						| factor
						;

unaryop 				: SUB
						| MUL
						| RAND
						;

factor					: immutable 
						| mutable
						;

mutable					: ID 
						| mutable LBRAC expression RBRAC 
						| mutable DOT ID
						;						

immutable				: LPAREN expression RPAREN 
						| call
						| constant 
						; 

call					: ID LPAREN args RPAREN 
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
						| expression
						;

constant	 			: NUMCONST 	
						| CHARCONST 
						| BOOLCONST 
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
